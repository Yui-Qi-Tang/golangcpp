#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <string.h>
#include "SetServerSocket.h"

int main(int argc, char* argv[]) {
    int server_port = 9999;
    char *server_ip = "127.0.0.1";    
    // start server
    SetServerSocket server(server_ip, server_port);

    server.start_server();
    //std::thread mThread(&SetServerSocket::start_server, &server);
    // client test
    // const int MAX_CLIENTS = 1024;
    // for(int i=0; i < MAX_CLIENTS; i++) {
    //     server.client_send_msg_test("Fuck bitch");
    // }
    
    //server.client_send_msg_test(argv[1]);
    return 0;    
}