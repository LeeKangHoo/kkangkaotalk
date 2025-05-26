#include "widget.h"

#include <QApplication>

struct Param{
    bool echo = false;
    bool broadcast = false;
    uint16_t port = 0;


    bool parse(int argc, char* argv[]){

        if (argc == 0){
            std::cout<<"syntax : echo-server <port> [-e[-b]]"<<std::endl;
            std::cout<<"sample : echo-server 1234 -e -b"<<std::endl;
            return false;
        }

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
}param;


int main(int argc, char *argv[])
{
    int socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ == -1) std::cout<<"socket error"<<std::endl;

    int bc_on = 1;
    setsockopt(socket_,SOL_SOCKET,SO_BROADCAST,&bc_on,sizeof(bc_on));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(param.port);


    ssize_t res = bind(socket_, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1) std::cout<<"bind error"<<std::endl;

    int res = listen(socket_,10);
    if (res == -1) std::cout<<"listen error"<<std::endl;

    while (true) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int socket_accept = accept(socket_,(struct sockaddr *)&addr, &len);
        if (socket_accept == -1) std::cout<<"accept error"<<std::endl;

        std::thread* t = new std::thread(recvThread, socket_accept);
        t->detach();
    }
    close(socket_);


    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
