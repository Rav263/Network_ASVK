#include <string>
#include <iostream>

#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"
#include "../headers/io_head.h"

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


    while(true) {
        int64_t command = IO::read_graph(graph);
        Net::send_vertex(&command, client->get_socket());
        if (command == -1) break;

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

        if (command == 0) {
            Mass path;

            Net::recv_vertex(&path, client->get_socket());

            if (path == -1) std::cout << "No path between this vertexes" << std::endl;
            else std::cout << "Your minimal path: " << path << std::endl;
        }

        if (command == 1) {
            ssize_t size;

            Net::recv_vertex(&size, client->get_socket());


            Vertex *path = new Vertex[size];

            Net::recv_array(path, size, client->get_socket());

            if (size == 0) {
                std::cout << "No path between this vertexes" << std::endl;
            } else {
                for (int i = 0; i < size - 1; i++) {
                    std::cout << path[i] << " -> ";
                }
                std::cout << path[size - 1] << std::endl;
            }
            delete[] path;
        }

        
    }
    delete client;
}
