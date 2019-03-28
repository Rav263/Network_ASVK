#include <string>
#include <iostream>


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

    while (true) {
        Vertex now = 0;

        Net::recv_vertex(&now, server.get_client());
        Vertex *arr = new Vertex[now];

        Net::recv_array(arr, now, server.get_client());
        std::cout << "Client send this numbers: " << now << std::endl;
        
        for(int i = 0; i < now; i++) std::cout << arr[i] << " ";
        std::cout << std::endl;
        
        delete[] arr;
    }
}
