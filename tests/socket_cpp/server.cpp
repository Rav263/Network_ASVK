#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

enum {
    PORT_NUM = 2917,
    BUF_SIZE = 1024,
};

int main() {
    
    std::cout << "Creating socket... ";
    int client = socket(AF_INET, SOCK_STREAM, 0);
    
    if (client < 0) {
        std::cout << "Faled" << std::endl;
        return 1;
    }
    std::cout << "Successfull" << std::endl;

    struct sockaddr_in socket_addr;

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = htons(INADDR_ANY);
    socket_addr.sin_port = htons(PORT_NUM);


    bind(client,(const sockaddr *) &socket_addr, sizeof(socket_addr));

    std::cout << "Waiting for client... " << std::endl;

    socklen_t size = sizeof(socket_addr);
    listen(client, 1);
    
    std::cout << "Connecting to client... " << std::endl;

    int server = accept(client, (struct sockaddr*) &socket_addr, &size);

    if (server < 0) {
        std::cout << "Faled" << std::endl;
        return 1;
    }

    std::cout << "Connected" << std::endl;

    close(server);
    close(client);
}
