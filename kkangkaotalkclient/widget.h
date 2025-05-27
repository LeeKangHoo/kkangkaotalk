#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <QWidget>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void appendMessage(QString msg);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void handleMessage(QString msg);

    void on_ptLog_blockCountChanged(int newBlockCount);

    void on_leChat_cursorPositionChanged(int arg1, int arg2);

    void on_pbSend_clicked();

    void on_leIp_cursorPositionChanged(int arg1, int arg2);

    void on_lePort_cursorPositionChanged(int arg1, int arg2);

    void on_pbConnect_clicked();

    void on_leName_cursorPositionChanged(int arg1, int arg2);

private:
    void recvThread(int socket_accept);
    void connectThread();
    int socket_ = -1;
    bool connected = false;
    Ui::Widget *ui;
};
#endif // WIDGET_H
