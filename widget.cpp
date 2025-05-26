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















void Widget::on_sendBtn_clicked()
{

}


void Widget::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{

}


void Widget::on_plainTextEdit_blockCountChanged(int newBlockCount)
{

}

