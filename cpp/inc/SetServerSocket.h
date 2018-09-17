#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> // socket close??

#include <stdio.h> // just for printf


class SetServerSocket {
    public:
        SetServerSocket(const char *ip, int port);
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
        
        bool server_send_msg(int guest_fd, char *msg);

        const char* get_client_msg(int guest_fd);

        void process_msg(int guest_fd, const char *msg);

        size_t len(const char *msg);

        void close_guest_fd(int guest_fd);

    private:
        const char *_ip;
        int _port;    
};