#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "SetServerSocket.h"

#include <thread> // for enable socket server as thread mode

int main(int argc, char* argv[]) {
    int server_port = 9999;
    const char *server_ip = "127.0.0.1";       
    // start server
    SetServerSocket server(server_ip, server_port);
    // server.start_server(); // enable socket server normally

    std::thread mThread(&SetServerSocket::start_server, &server); // enable server via thread

    // client test
    const int MAX_CLIENTS = 5;
    for(int i=0; i < MAX_CLIENTS; i++) {
        server.client_send_msg_test("Hi Server!, I am here!");
    }
    
    return 0;
}
