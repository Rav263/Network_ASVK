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
    
    delete[] ver_arr;
    delete client;
}
