#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this,&Widget::appendMessage, this, &Widget::handleMessage);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::handleMessage(QString msg){
    ui->ptLog->appendPlainText(msg);
}

void Widget::serverThread(){
    int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ == -1) emit appendMessage(QString("socket error"));

    int opt = 1;
    setsockopt(socket_,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);


    ssize_t res = bind(socket_, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) emit appendMessage(QString("bind error"));

    res = listen(socket_,10);
    if (res == -1) emit appendMessage(QString("listen error"));

    //bool check_first = false;

    while (true) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int socket_accept = accept(socket_,(struct sockaddr *)&addr, &len);
        if (socket_accept == -1){
            emit appendMessage(QString("accept error"));
            continue;
        }

        if (client.find(socket_accept) == client.end()){
            emit appendMessage(QString("New connection: %1").arg(socket_accept));
            char tmp_buf[65536];
            memset(tmp_buf,0,sizeof(tmp_buf));
            ssize_t recv_len = recv(socket_accept, tmp_buf, 65536 - 1, 0);
            if (recv_len > 0) {
                tmp_buf[recv_len] = '\0';
            }

            client.insert({socket_accept,tmp_buf});
            //sockets.insert(socket_accept);
            std::thread* t = new std::thread(&Widget::recvThread,this, socket_accept,tmp_buf);
            t->detach();
            continue;
        }
        emit appendMessage(QString("Existing connection?: %1").arg(socket_accept));

        /*char tmp_buf[65536];
        recv(socket_accept, tmp_buf, 65536 - 1, 0);
        char* client_name = client.find(socket_accept)->second;*/

        std::thread* t = new std::thread(&Widget::recvThread,this, socket_accept,client.find(socket_accept)->second.c_str());
        t->detach();
    }

    ::close(socket_);
}

void Widget::recvThread(int socket_accept,const char* client_name){
    emit appendMessage(QString("%1 Connected").arg(client_name));
    emit appendMessage(QString("Socket: %1, Name: %2").arg(socket_accept).arg(client_name));
    char buf[65536];
    char msg[65536];
    while (true){
        ssize_t res = recv(socket_accept,buf,65536-1,0);
        memset(msg,0,sizeof(msg));
        if (res == 0 || res == -1){
            emit appendMessage(QString("recv error"));
            break;
        }
        buf[res] = '\0';
        emit appendMessage(QString("%1 : %2").arg(client.find(socket_accept)->second).arg(buf));

        if (echo){
            std::string msg_e =  std::string("Me : ") + buf;
            send(socket_accept,msg_e.c_str(),msg_e.length(),0);
        }
        if (broadcast){
            std::string msg_b = std::string(client.find(socket_accept)->second) + " : " + buf;
            for( std::pair<const int,std::string> i : client){
                if(i.first != socket_accept){
                    send(i.first,msg_b.c_str(),msg_b.length(),0);
                }
            }
        }
    }
    client.erase(socket_accept);
    //sockets.erase(socket_accept);

    emit appendMessage(QString("%1 Disconnected").arg(client_name));
    ::close(socket_accept);
}

void Widget::on_ptLog_blockCountChanged(int newBlockCount)
{

}


void Widget::on_lePort_cursorPositionChanged(int arg1, int arg2)
{

}


void Widget::on_openBtn_clicked()
{
    port = ui->lePort->text().toUShort();
    emit appendMessage(QString("서버 시작: 포트 %1").arg(port));
    std::thread* server = new std::thread(&Widget::serverThread,this);
    server->detach();
}


void Widget::on_chEcho_checkStateChanged(const Qt::CheckState &arg1)
{
    echo = (arg1 == Qt::Checked);
}


void Widget::on_chBroadcast_checkStateChanged(const Qt::CheckState &arg1)
{
    broadcast = (arg1 == Qt::Checked);
}

