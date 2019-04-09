#include <string>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"
#include "../headers/dijkstra.h"
#include "../headers/io_head.h"


enum {
    BUF_SIZE = 1024,
};

int main() {
    int port;
    std::cout << "Please enter port: ";
    std::cin >> port;

    Net::ServerSocket server(port);
    server.set_socket_available_mode();
    
    int pid;

    while ((pid = server.accept_client()) == 0);
    
    std::cout << "PID: " << pid << std::endl;

    while (true) {
        Vertex now = 0;

        int64_t command;
        Net::recv_vertex(&command, server.get_client());

        if (command == -1) break;

        Net::recv_vertex(&now, server.get_client());
        Vertex *arr = new Vertex[now];

        Net::recv_array(arr, now, server.get_client());
    
        NetworkGraph graph;
        create_graph_from_array(arr, now, graph);

        Vertex start, end;
        Net::recv_vertex(&start, server.get_client());
        Net::recv_vertex(&end, server.get_client());

        IO::print_graph(graph);
    
        Path path;

        Mass dist = calc_path(path, graph.get_full_graph(), start, end);
        if (command == 0) {
            Net::send_vertex(&dist, server.get_client());
        } 

        if (command == 1) {
            ssize_t size = path.size();
            if (dist == -1) size = 0;
            Net::send_vertex(&size, server.get_client());
            
            Vertex *path_arr = new Vertex[path.size()];

            for (int i = 0; i < path.size(); i++) {
                path_arr[i] = path[i];
            }

            Net::send_array(path_arr, path.size(), server.get_client());

            delete[] path_arr;
        }
        delete[] arr;
    }
    server.close_client();

    Logs::logln("End client session");

    while(wait(NULL) != -1);
}
