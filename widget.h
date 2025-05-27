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
#include <thread>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void appendMessage(Qtring& msg);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_ptLog_blockCountChanged(int newBlockCount);

    void on_lePort_cursorPositionChanged(int arg1, int arg2);

    void on_openBtn_clicked();

    void on_chEcho_checkStateChanged(const Qt::CheckState &arg1);

    void on_chBroadcast_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
