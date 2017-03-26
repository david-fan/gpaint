/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "eraserinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"
#include <QtCore/qmath.h>
#include <QPen>
#include <QPainter>
#include <QDebug>

EraserInstrument::EraserInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void EraserInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        makeUndoCommand(imageArea);
        erasePoint(imageArea,mStartPoint);
    }
count=0;
}

void EraserInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mStartPoint = event->pos();
        erease(imageArea);
        mEndPoint = event->pos();
//        paint(imageArea, false);
//        mStartPoint = event->pos();
    }
    count++;
}

void EraserInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
//        paint(imageArea);
        imageArea.setIsPaint(false);
    }
    qDebug()<<count;
    count=0;
}

void EraserInstrument::paint(ImageArea &imageArea, bool, bool)
{
    QPainter painter(imageArea.getImage());
    painter.setPen(QPen(Qt::white,
                        DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(QBrush(Qt::transparent));
//    painter.eraseRect();
    if(mStartPoint != mEndPoint)
    {
        painter.drawLine(mStartPoint, mEndPoint);
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }
    imageArea.setEdited(true);
    //    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
    //                                                                 (mStartPoint.x() - mEndPoint.x()) +
    //                                                                 (mStartPoint.y() - mEndPoint.y()) *
    //                                                                 (mStartPoint.y() - mEndPoint.y()))));
    //    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    imageArea.update();
}

void EraserInstrument::erease(ImageArea &imageArea)
{
    if(mStartPoint != mEndPoint)
    {
        int sx = mEndPoint.x()-mStartPoint.x();
        int sy = mEndPoint.y()-mStartPoint.y();
        int i,m;
        if(sx!=0){
            float k = sy/sx;
            for(i=0;i<=qAbs(sx);i++){
                m=(sx>0)?1:-1;
                QPoint p(mStartPoint.x()+i*m,mStartPoint.y()+i*k*m);
                erasePoint(imageArea,p);
            }
        }
        else{
            for(i=0;i<=qAbs(sy);i++){
                m=(sy>0)?1:-1;
                QPoint p(mStartPoint.x(),mStartPoint.y()+i*m);
                erasePoint(imageArea,p);
            }
        }

    }

    if(mStartPoint == mEndPoint)
    {
//        qDebug()<<mStartPoint;
        erasePoint(imageArea,mStartPoint);
    }
    imageArea.setEdited(true);
    imageArea.update();

}

void EraserInstrument::erasePoint(ImageArea &imageArea,QPoint p)
{
    int r = 10;
    for(int x=-r;x<=r;x++){
        int y = qRound(qSqrt(qPow(r,2)-qPow(x,2)));
        for(int i=p.y()-y;i<=p.y()+y;i++){
                imageArea.getImage()->setPixelColor(p.x()+x,i,Qt::transparent);
        }
    }
}
