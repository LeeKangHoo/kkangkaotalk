#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this,&Widget::appendMessage,this,&Widget::handleMessage);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handleMessage(QString msg){
    ui->ptLog->appendPlainText(msg);
}

void Widget::recvThread(int socket_accept){
    char buf[65536];
    while(true){
        ssize_t res= recv(socket_accept,buf,65536-1,0);
        if (res <= 0){
            emit appendMessage("recv error");
            break;
        }
        buf[res]='\0';
        emit appendMessage(QString::fromUtf8(buf));
    }
    ::close(socket_accept);
}

void Widget::on_ptLog_blockCountChanged(int newBlockCount)
{

}


void Widget::on_leChat_cursorPositionChanged(int arg1, int arg2)
{

}


void Widget::on_pbSend_clicked()
{
    if(!connected) emit appendMessage("Not connected");
    std::string msg = ui->leChat->text().toStdString();
    int res = send(socket_,msg.c_str(),msg.length(),0);
    if (res == -1) emit appendMessage("send error");

    ui->leChat->clear();
}


void Widget::on_leIp_cursorPositionChanged(int arg1, int arg2)
{

}


void Widget::on_lePort_cursorPositionChanged(int arg1, int arg2)
{

}


void Widget::on_pbConnect_clicked()
{
    if(connected){
        ::close(socket_);
        connected = false;
        ui->pbConnect->setText("Connect");
        emit appendMessage("Disconnected");
        return;
    }
    std::thread* t = new std::thread(&Widget::connectThread, this);
    t->detach();



}
void Widget::connectThread(){
    socket_ = ::socket(AF_INET,SOCK_STREAM,0);
    if(socket_==-1) {
        emit appendMessage("socket error");
        return;
    }
    if(socket_==-1) emit appendMessage("socket error");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ui->leIp->text().toLatin1().constData(), &addr.sin_addr);
    addr.sin_port = htons(ui->lePort->text().toUShort());



    int res = ::connect(socket_,(struct sockaddr*)&addr,sizeof(addr));
    if (res == -1) emit appendMessage("connect error");
    connected = true;
    ui->pbConnect->setText("Disconnect");
    emit appendMessage("Connected");

    QString name = ui->leName->text();
    send(socket_, name.toStdString().c_str(), name.length(), 0);

    std::thread* t = new std::thread(&Widget::recvThread,this,socket_);
    t->detach();

}


void Widget::on_leName_cursorPositionChanged(int arg1, int arg2)
{

}

