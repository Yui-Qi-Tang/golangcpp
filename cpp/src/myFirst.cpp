#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <string.h>

#include "SetServerSocket.h"


int create_client_fd() {

    int client_fd = -1;
    //memset(&client, 0, sizeof(client)); // init client; windows env doesnot support this function
    // set client socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        printf("can not create client fd: %d\n", client_fd);
        return  client_fd;
    }
    printf("client fd is: %d\n", client_fd);
    return client_fd;
}

bool client_connect(char *ip, int port, int client_fd) {
    int isConnect = -1;
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(ip);
    client.sin_port = htons(port);

    isConnect = connect(client_fd, (struct sockaddr *)&client, sizeof(client));
    if(isConnect < 0) {
        return false;
    }
    return true;

}

bool client_send_msg(int client_fd, char *msg) {
    int success = send(client_fd, msg, strlen(msg), 0);
    if (success < 0) {
        return false;
    }
    else {
        return true;
    }
}

int main(int argc, char* argv[]) {
    int server_port = 9999;
    char *server_ip = "127.0.0.1";
    
    int client_fd = -1;
    bool isConnect = false;

    SetServerSocket server(server_ip, server_port);
    std::thread mThread(&SetServerSocket::start_server, &server);

    // client
    client_fd = create_client_fd();
    isConnect = client_connect(server_ip, server_port, client_fd);
    if(isConnect) {
        printf( "Client connects to server has been successed!! \n");
    }
    // send msg
    if(client_send_msg(client_fd, "Hi, I am Yuki Tang")) {
        printf("send success \n");
    }
    else {
        printf("Send failed! \n");
    }
    
    return 0;    
}