#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

enum {
    PORT_NUM = 2917,
};


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "NO IP" << std::endl;
        return 1;
    }
    
    std::cout << "Creating socket.. ";
    int client = socket(AF_INET, SOCK_STREAM, 0);
    
    if (client < 0) {
        std::cout << "Falied" << std::endl;
        return 1;
    }

    std::cout << "Successfull" << std::endl;

    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUM);

    std::cout << "Connecting... ";

    int status = connect(client, (struct sockaddr *) &server, sizeof(server));

    if (status < 0) {
        std::cout << "Falied" << std::endl;

        return 1;
    }

    std::cout << "Successfull" << std::endl;

    sleep(5);

    close(client);
}
