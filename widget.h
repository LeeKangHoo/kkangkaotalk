#ifndef WIDGET_H
#define WIDGET_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <QWidget>
#include <arpa/inet.h>
#include <sys/socket.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_sendBtn_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_plainTextEdit_blockCountChanged(int newBlockCount);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
