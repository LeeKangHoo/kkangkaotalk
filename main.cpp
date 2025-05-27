#include "widget.h"

#include <QApplication>

/*
std::map<uint32_t,std::string> client;
std::set<int> sockets;

struct Setting{
    bool echo = false;
    bool broadcast = false;
    uint16_t port = 0;


    bool parse(int argc, char* argv[]){
        for (int i = 2; i < argc;){
            if(strcmp(argv[i], "-e") == 0) {
                echo = true;
                i++;
            }
            if (strcmp(argv[i], "-b") == 0) {
                broadcast = true;
                i++;
            }
        }
        port = atoi(argv[1]);
        return port != 0;
    }
}conf;


void recvThread(int socket_accept,char* client_name,uint32_t client_ip){
    std::cout<<client_name<<" Connected"<<std::endl;
    char buf[65536];
    char msg[65536];
    while (true){
        ssize_t res = recv(socket_accept,buf,65536-1,0);
        memset(msg,0,sizeof(msg));
        if (res == 0 || res == -1){
            std::cout<<"recv error "<<client_name<<std::endl;
            break;
        }
        buf[res] = '\0';

        if (conf.echo){
            std::string msg_e =  std::string("Me : ") + buf;
            send(socket_accept,msg_e.c_str(),msg_e.length(),0);
        }
        if (conf.broadcast){
            std::string msg_b = std::string(client_name) + " : " + buf;
            for(int i : sockets){
                if(i != socket_accept){
                    send(i,msg_b.c_str(),msg_b.length(),0);
                }
            }
        }
    }
    client.erase(client_ip);
    sockets.erase(socket_accept);

    std::cout<<client_name<<" Disconnected"<<std::endl;
    close(socket_accept);
}

void serverThread(){
    int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ == -1) std::cout<<"socket error"<<std::endl;

    int opt = 1;
    setsockopt(socket_,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(param.port);


    ssize_t res = bind(socket_, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) std::cout<<"bind error"<<std::endl;

    res = listen(socket_,10);
    if (res == -1) std::cout<<"listen error"<<std::endl;

    //bool check_first = false;

    while (true) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int socket_accept = accept(socket_,(struct sockaddr *)&addr, &len);
        if (socket_accept == -1) std::cout<<"accept error"<<std::endl;

        if (client.find(addr.sin_addr.s_addr) == client.end()){
            char tmp_buf[65536];
            recv(socket_accept, tmp_buf, 65536 - 1, 0);
            client.insert({addr.sin_addr.s_addr,tmp_buf});
            sockets.insert(socket_accept);
            std::thread* t = new std::thread(recvThread, socket_accept,tmp_buf,addr.sin_addr.s_addr);
            t->detach();
            continue;
        }

        char tmp_buf[65536];
        recv(socket_accept, tmp_buf, 65536 - 1, 0);
        sockets.insert(socket_accept);
        std::thread* t = new std::thread(recvThread, socket_accept,tmp_buf,addr.sin_addr.s_addr);
        t->detach();
    }
    close(socket_);
}*/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();
/*
    std::thread server(serverThread);
    server.detach();
*/
    return a.exec();
}
