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
    void appendMessage(QString msg);


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void handleMessage(QString msg);

    void on_ptLog_blockCountChanged(int newBlockCount);

    void on_lePort_cursorPositionChanged(int arg1, int arg2);

    void on_openBtn_clicked();

    void on_chEcho_checkStateChanged(const Qt::CheckState &arg1);

    void on_chBroadcast_checkStateChanged(const Qt::CheckState &arg1);

private:
    void serverThread();
    void recvThread(int socket_accept, char* client_name, uint32_t client_ip);

    Ui::Widget *ui;
    std::map<uint32_t, std::string> client;
    std::set<int> sockets;
    bool echo = false;
    bool broadcast = false;
    uint16_t port = 0;
};
#endif // WIDGET_H
