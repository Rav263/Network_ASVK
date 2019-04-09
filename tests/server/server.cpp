#include <iostream>
#include "sockets.h"
#include <vector>


int main() {
    Net::ServerSocket server(2222);

    server.set_socket_available_mode();
    while(true) {
    server.accept_client();

    std::vector<char> str;
    char some[100];
    while (true) {
        ssize_t now = recv(server.get_client(), some, 100, 0);
        if (now == 0) break;
        for (int i = 0; i < now; i++) {
            str.push_back(some[i]);
        }
    }
    for (auto now : str) {
        std::cout <<(int) now;
    }
    std::cout << std::endl;
    }

}
