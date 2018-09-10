#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]) {
    struct sockaddr_in client;
    char *server_ip = "127.0.0.1";
    int server_port = 54756;
    const short int SOCKET_ERROR = -1;
    const short int CONNECT_SOCKET_ERROR = -1;
    int client_fd = -1;
    int connectStatus;

    memset(&client, 0, sizeof(client)); // init client
    // set client socket data
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(server_port);

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == SOCKET_ERROR) {
        cerr << "client open socket failed: " << client_fd << " (socket code)" << endl;
        return 0;
    }
    else {
        cout << "Open socket success!" << endl;
    }

    // try connect server
    for(int i = 0; i< 10; i++) {
        connectStatus = connect(client_fd, (struct sockaddr *)&client, sizeof(client));
        if(connectStatus == CONNECT_SOCKET_ERROR) {
            cerr << "connect to client_fd failed: " << connectStatus << " (connect status code)" << endl;
        }
        else {
            cout << "connect success!!" << endl;
        }
    }


    return 0;
}