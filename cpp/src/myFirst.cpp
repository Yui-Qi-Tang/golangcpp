#include <iostream>
#include <stdexcept>
/*
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <netinet/in.h> 

#include <thread>
*/
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
using namespace std;

void checkIfInt(char*);
void showCommand(char* args[]);

#define PORT 9000

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
    int server_addr_len = sizeof(server_addr);
    accept(fd_socket, (struct sockaddr *)&server_addr, (socklen_t *)&server_addr_len);


    return fd_socket;
} // socket_listen()

void server_accpet(int fd_server, int server_port) {
    int fd_guest = -1;
    if(fd_server == -1) {
        printf("Server failed!");
        exit(0);
    }
    printf("server started at %s:%d ...\n", "127.0.0.1", server_port);
    while(1) {
        cout << "waitting..." << endl;
        fd_guest = accept(fd_server, (struct sockaddr *)NULL, NULL);
        printf("accept status %d\n", fd_guest);
    }
}


int main(int argc, char* argv[]) {
    // int fd_server = -1;
    // int server_port = 9999;
    // fd_server = socket_listen(server_port);
    // server_accpet(fd_server, server_port);
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
    // { 
    //     perror("setsockopt"); 
    //     exit(EXIT_FAILURE); 
    // } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    // Forcefully attaching socket to the port 8080 
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    // if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    // { 
    //     perror("bind failed"); 
    //     exit(EXIT_FAILURE); 
    // } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }
    std::cout << "Hi" << endl;
    if ((new_socket = accept(server_fd, (struct sockaddr *)NULL, NULL))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    return 0;    
}

void showCommand(char* args[]) {
    std::cout << ":" << args << "\n"; 
}

void checkIfInt(char *str) {
    std::string arg = str;
    try {
      std::size_t pos;
      int x = std::stoi(arg, &pos);
      if (pos < arg.size()) {
        std::cerr << "Trailing characters after number: " << arg << '\n';
      }
      std::cout << x + 1 << std::endl;
    } catch (std::invalid_argument const &ex) {
      std::cerr << "Invalid number: " << arg << '\n';
    } catch (std::out_of_range const &ex) {
      std::cerr << "Number out of range: " << arg << '\n';
    }

}