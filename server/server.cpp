#include <string>
#include <iostream>


#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"
#include "../headers/dijkstra.h"

enum {
    PORT_NUM = 2917,
    BUF_SIZE = 1024,
};

int main() {
    Net::ServerSocket server(PORT_NUM);
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

    std::cout << path.size() << " " << path[0].second << std::endl;

    delete[] arr;
}
