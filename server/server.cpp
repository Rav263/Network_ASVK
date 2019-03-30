#include <string>
#include <iostream>


#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"
#include "../headers/dijkstra.h"

enum {
    BUF_SIZE = 1024,
};

int main() {
    int port;
    std::cout << "Please enter port: ";
    std::cin >> port;

    Net::ServerSocket server(port);
    server.set_socket_available_mode();
    server.accept_client();

    Vertex now = 0;

    Net::recv_vertex(&now, server.get_client());
    Vertex *arr = new Vertex[now];

    Net::recv_array(arr, now, server.get_client());
    
    NetworkGraph graph;
    create_graph_from_array(arr, now, graph);

    Vertex start, end;
    Net::recv_vertex(&start, server.get_client());
    Net::recv_vertex(&end, server.get_client());

    print_graph(graph);
    
    Path path;

    calc_path(path, graph.get_full_graph(), start, end);
    Net::send_vertex(&path[0].second, server.get_client());

    delete[] arr;
}
