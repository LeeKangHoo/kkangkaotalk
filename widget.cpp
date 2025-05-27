#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}











void appendMessage(QString& msg){
    ui->ptLog->appendPlainText(msg);
}


void Widget::on_ptLog_blockCountChanged(int newBlockCount)
{

}


void Widget::on_lePort_cursorPositionChanged(int arg1, int arg2)
{

}


void Widget::on_openBtn_clicked()
{

}


void Widget::on_chEcho_checkStateChanged(const Qt::CheckState &arg1)
{

}


void Widget::on_chBroadcast_checkStateChanged(const Qt::CheckState &arg1)
{

}

