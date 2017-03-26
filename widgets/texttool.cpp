#include "texttool.h"

TextTool::TextTool(QWidget *parent):QWidget(parent)
{
    this->increase = new QPushButton("+",this);
    this->decrease = new QPushButton("-",this);
    this->move = new QPushButton("Move",this);
    this->resize = new QPushButton("Risize",this);
    this->te = new QTextEdit(this);
    this->te->setFrameStyle(QFrame::NoFrame);
    this->m_finish = new QPushButton("OK",this);
}
