#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


#include <stdio.h> // just for printf


class SetServerSocket {
    public:
        SetServerSocket(char * ip, int port);
        ~SetServerSocket();

        void start_server();
        void client_send_msg_test(char *msg);
        
    private:
        void showRecvMsg(int guest_fd);
        int socket_listen();
        int new_guest_fd(int fd_server);

        int create_client_fd();
        bool client_connect(int client_fd);
        bool client_send_msg(int client_fd, char *msg);

    private:
        char *_ip;
        int _port;    
};