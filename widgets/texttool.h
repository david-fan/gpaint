#ifndef TEXTTOOL_H
#define TEXTTOOL_H

#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class TextTool : public QWidget
{
public:
    TextTool(QWidget *parent);
    QString getText();
    void setText(QString text);
private:
    QPushButton *increase;
    QPushButton *decrease;
    QPushButton *move;
    QPushButton *resize;
    QPushButton *m_finish;
    QPushButton *m_cancle;
    QTextEdit *te;
signals:
    void finish();
    void cancle();
};

#endif // TEXTTOOL_H
