#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "sockets.h"


enum {
    PORT_NUM = 2917,
    BUF_SIZE = 1024,
};

int main() {

    Net::ServerSocket server(PORT_NUM);

    bind(server.get_socket(),(const sockaddr *) server.get_sock_addr(), server.get_sock_addr_size());

    std::cout << "Waiting for client... " << std::endl;

    socklen_t size = server.get_sock_addr_size();
    listen(server.get_socket(), 1);
    
    std::cout << "Connecting to client... " << std::endl;

    int client = accept(server.get_socket(), (struct sockaddr*) server.get_sock_addr(), &size);

    if (client < 0) {
        std::cout << "Faled" << std::endl;
        return 1;
    }

    std::cout << "Connected" << std::endl;

    close(client);
}
