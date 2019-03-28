#include <string>
#include <iostream>

#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"

enum {
    PORT_NUM = 2917,
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Logs::logln_err("NO_IP");
        return 1;
    }

    Net::ClientSocket *client = new Net::ClientSocket(PORT_NUM, std::string(argv[1]));
    client->connect_to_server();

    Vertex now;

    while (true) {
        std::cout << "Please enter array_size: ";
        std::cin >> now;
        Net::send_vertex(&now, client->get_socket());

        Vertex *arr = new Vertex[now];

        for (int i = 0; i < now; i++) {
            std::cin >> arr[i];
        }

        Net::send_array(arr, now, client->get_socket());
        delete[] arr;
    }
    delete client;
}
