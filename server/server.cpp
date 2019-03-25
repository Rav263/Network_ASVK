#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"


enum {
    PORT_NUM = 2917,
    BUF_SIZE = 1024,
};

int main() {
    Net::ServerSocket server(PORT_NUM);
    server.set_socket_available_mode();
    server.accept_client();
}