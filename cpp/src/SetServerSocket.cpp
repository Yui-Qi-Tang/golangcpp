#include "SetServerSocket.h"

/* 建構子 */
SetServerSocket::SetServerSocket(char *ip, int port) {
    _ip = ip;
    _port = port;   
}

/* 解構子*/
SetServerSocket::~SetServerSocket() {
    delete _ip;
}

/* 開啟socket server */
void SetServerSocket::start_server() {
    int server_fd = socket_listen();

    while(0x1) {
        int new_fd = -1;
        new_fd = new_guest_fd(server_fd);
        if(new_fd < 0){
			printf("accept new guest failed!!");
			continue;
		}
        printf("New guest!!\n");

        showRecvMsg(new_fd);

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
	int has_new_msg = recv(guest_fd, buf, sizeof(buf), 0);
	if (has_new_msg > 0) {
		printf("Server get guest msg: %s\n", buf);
	}
	else {
		printf("recv failed!\n");
	}
}
