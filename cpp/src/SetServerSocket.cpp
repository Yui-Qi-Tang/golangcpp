#include "SetServerSocket.h"

/* 建構子 */
SetServerSocket::SetServerSocket(const char *ip, int port) {
    _ip = ip;
    _port = port;   
}

/* 解構子*/
SetServerSocket::~SetServerSocket() {
    // delete _ip;
}

/* 開啟socket server */
void SetServerSocket::start_server() {
    int server_fd = socket_listen();
    printf("Server starting...\n");
    while(0x1) {
        int new_fd = -1;
        printf("Waitting for new client...\n");
        new_fd = new_guest_fd(server_fd);
        if(new_fd < 0){
			printf("accept new guest failed!!\n");
			continue;
		}
        printf("New guest, the fd is: * %d *!!\n", new_fd);
        process_msg(new_fd, get_client_msg(new_fd));
        /*
        printf("get cmd from client: %s\n", client_cmd);
        printf("Respone for client...");
        char *clientMsg = "client exit1";
        if(
            write(new_fd, clientMsg, strlen(clientMsg)) < 0 
        )
        {
            printf("send failed\n");
        }
        else {
            printf("server sends ok\n");
        }
        */
        //close(new_fd);

    }

}

/* socket server-side setting */
int SetServerSocket::socket_listen() {
    int fd_socket;
    struct sockaddr_in server_addr;

    // 建立一個 NONBLOCK 的 STREAM (串流) socket
    fd_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 清空server_addr
    memset(&server_addr, 0, sizeof(server_addr));

    // 設定預定的主機地址，通訊埠 (port)
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(_port);

    // 將 fd_socket 和伺服地址資訊 *綁定*
    bind(fd_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // 開始 *聆聽* (listen) 連線要求
    listen(fd_socket, 10);

    // 回傳 fd_socket
    return fd_socket;
}

/* 回傳連線資訊  */
int SetServerSocket::new_guest_fd(int fd_server) {
    int fd_guest = -1;
    if(fd_server == -1) {
        return -1;
    }
    fd_guest = accept(fd_server, (struct sockaddr *)NULL, NULL);
    return fd_guest;
}

/* 接收訊息 */
void SetServerSocket::showRecvMsg(int guest_fd) {
    printf("Check recv\n");
    const int MAX_MSG_BUF_SIZE = 8192;
	char buf[MAX_MSG_BUF_SIZE];
    // char* buf;
    memset(buf, 0, sizeof(buf)); // init client; windows env doesnot support this function

    printf("Size of buf is %lu\n", sizeof(buf)); // long unsigned int sizeof()
	int has_new_msg = recv(guest_fd, buf, sizeof(buf), 0);
    int len = 0;
    while(buf[len] != '\0') {
        len++;
    }
    printf("buf data counts: %d\n", len);
	if (has_new_msg > 0) {
		printf("Server get guest %d msg: %s\n", guest_fd, buf);
	}
	else {
		printf("recv failed!\n");
	}
}

/* create client fd */
int SetServerSocket::create_client_fd() {
    int client_fd = -1;
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        printf("can not create client fd: %d\n", client_fd);
        return  client_fd;
    }
    printf("client fd is: %d\n", client_fd);
    return client_fd;
}

/* client socket connect wrapper, return connect status */
bool SetServerSocket::client_connect(int client_fd) {
    int isConnect = -1;
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client)); // init client; windows env doesnot support this function
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(_ip);
    client.sin_port = htons(_port);

    isConnect = connect(client_fd, (struct sockaddr *)&client, sizeof(client));
    if(isConnect < 0) {
        return false;
    }
    return true;

}

/* client connect test */
void SetServerSocket::client_send_msg_test(char *msg){
    // client
    bool isConnect = false;
    int client_fd = -1;
    client_fd = create_client_fd();
    isConnect = client_connect(client_fd);
    if(isConnect) {
        printf( "Client connects to server has been successed!! \n");
        client_send_msg(client_fd, msg);
    }
}

/* client send msg */
bool SetServerSocket::client_send_msg(int client_fd, char *msg) {
    int success = send(client_fd, msg, strlen(msg), 0);
    if (success < 0) {
        return false;
    }
    else {
        return true;
    }
}

/* server send msg to client */
bool SetServerSocket::server_send_msg(int guest_fd, char *msg) {
    int success = send(guest_fd, msg, strlen(msg), 0);
    if (success < 0) {
        return false;
    }
    else {
        return true;
    }
}

/* return msg from client */
const char* SetServerSocket::get_client_msg(int guest_fd) {
    const int MAX_MSG_BUF_SIZE = 8192;
	char buf[MAX_MSG_BUF_SIZE];
    const char *ptr = buf;
    memset(buf, 0, sizeof(buf)); // init client; windows env doesnot support this function
	int has_new_msg = recv(guest_fd, buf, sizeof(buf), 0);
    return ptr;
}

/* process msg from client */
void SetServerSocket::process_msg(int guest_fd, const char *msg) {
    printf("get msg from client: %s\n", msg);
    const char *QUIT = "quit";
    const char *BYE = "release";
    const char *HELLO = "Hello!";
    if(strcmp(msg, QUIT) == 0 ) {
        send(guest_fd, BYE, len(BYE), 0);
        close_guest_fd(guest_fd);
    }
    else {
        send(guest_fd, HELLO, len(HELLO), 0);
    }
}

/* get const char* size */
size_t SetServerSocket::len(const char *msg) {
    size_t size = 0;
    char NULL_CHAR = '\0';
    while(*(msg+size) != NULL_CHAR) {
        size++;
    }
    return size;
}

/* close guest fd */
void SetServerSocket::close_guest_fd(int guest_fd) {
    printf("Close guest fd: %d...\n", guest_fd);
    close(guest_fd);
}