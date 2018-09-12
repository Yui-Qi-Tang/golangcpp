#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


#include <stdio.h> // just for printf


class SetServerSocket {
    public:
        SetServerSocket(char * ip, int port);
        ~SetServerSocket();

        void start_server();
    private:
        void showRecvMsg(int guest_fd);
        int socket_listen();
        int new_guest_fd(int fd_server);

    private:
        char *_ip;
        int _port;    
};