#include <string>
#include <iostream>

#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"

int main(int argc, char *argv[]) {
    int port;
    std::string ip;

    std::cout << "Please enter IP: ";
    std::cin >> ip;

    std::cout << "Please enter PORT: ";
    std::cin >> port;
    
    Net::ClientSocket *client = new Net::ClientSocket(port, ip);
    client->connect_to_server();

    Vertex now;

    NetworkGraph graph;

    read_graph(graph);
    print_graph(graph);

    ssize_t size;

    Vertex *ver_arr = create_arr_from_graph(graph.get_full_graph(), size);

    std::cout << "Please enter start and end vertex" << std::endl;
    Vertex start, end;

    std::cin >> start >> end;

    Net::send_vertex(&size, client->get_socket());

    Net::send_array(ver_arr, size, client->get_socket());
    Net::send_vertex(&start, client->get_socket());
    Net::send_vertex(&end, client->get_socket());

    Mass path;

    Net::recv_vertex(&path, client->get_socket());

    std::cout << "Your minimal path: " << path << std::endl;

    delete[] ver_arr;
    delete client;
}
