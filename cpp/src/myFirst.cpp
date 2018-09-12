#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <string.h>

int socket_listen(int port) {
    int fd_socket;
    struct sockaddr_in server_addr;

    // 建立一個 NONBLOCK 的 STREAM (串流) socket
    fd_socket = socket(AF_INET, SOCK_STREAM, 0);

    // memset(&server_addr, 0, sizeof(server_addr));

    // 設定預定的主機地址，通訊埠 (port)
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    //server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(port);

    // 將 fd_socket 和伺服地址資訊 *綁定*
    bind(fd_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // 開始 *聆聽* (listen) 連線要求
    listen(fd_socket, 10);

    return fd_socket;
} // socket_listen()

void server_accpet(int fd_server, int server_port) {
    int fd_guest = -1;
    if(fd_server == -1) {
        printf("Server failed!");
        exit(0);
    }
    printf("server started at %s:%d ...\n", "127.0.0.1", server_port);
    fd_guest = accept(fd_server, (struct sockaddr *)NULL, NULL);
    printf("accept status %d\n", fd_guest);
}

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
    int fd_server = -1;
    int server_port = 9999;
    int client_fd = -1;
    bool isConnect = false;
    char *server_ip = "127.0.0.1";
    // fd_server = socket_listen(server_port);
    // if(fd_server < 0) {
    //     printf("can not create server fd, fd code: %d\n", fd_server);
    // }
    // std::thread mThread( server_accpet, fd_server, server_port ); // add serever_accept to thread pool

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