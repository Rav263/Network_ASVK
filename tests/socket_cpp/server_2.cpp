#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "sockets.h"
#include "logs.h"

enum {
    PORT_NUM = 2917,
    BUF_SIZE = 1024,
};

int main() {

    Net::ServerSocket server(PORT_NUM);

    Logs::logln("Waiting for client... ");

    socklen_t size = server.get_sock_addr_size();
    listen(server.get_socket(), 1);
    
    Logs::log("Connecting to client... ");

    int client = accept(server.get_socket(), (struct sockaddr*) server.get_sock_addr(), &size);

    if (client < 0) {
        Logs::logln_err("Faled");
        return 1;
    }

    Logs::logln("Successfull");

    close(client);
}
