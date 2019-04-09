#include <string>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <sstream>


#include "../headers/sockets.h"
#include "../headers/logs.h"
#include "../headers/network.h"
#include "../headers/dijkstra.h"
#include "../headers/io_head.h"


enum {
    PORT = 19121,
    BUF_SIZE = 1024,
};
void recv_buffer(int socket, char *buffer, ssize_t len) {
    ssize_t readed = 0;

    while (readed != len) {
        ssize_t tmp = recv(socket, (char *)buffer + readed, len - readed, 0);
            
        if (tmp < 0) throw 1;
        readed += tmp;
    }
}

Vertex *get_data(Net::ServerSocket &server, Vertex &start, Vertex &end, ssize_t &size) {

    int buf_size;

    recv(server.get_client(), &buf_size, sizeof(buf_size), 0);
  
    char *buff = new char[buf_size];

    recv_buffer(server.get_client(), buff, buf_size);

    std::string data(buff);

    std::stringstream in_str(data);

    std::vector<Vertex> nums;

    Vertex now;

    while (in_str >> now) nums.push_back(now);
    Vertex *vertexes = new Vertex[nums.size()];


    for (size_t i = 0; i < nums.size() - 2; i++) vertexes[i] = nums[i];
    start = nums[nums.size() - 2];
    end = nums[nums.size() - 1];
    size = nums.size() - 2;

    return vertexes;
}

void create_result(std::string &res, Path &path, Mass &dist) {
    std::ostringstream out_str;

    for (int i = 0; i < path.size() - 1; i++) {
        out_str << path[i] << " -> ";
    }

    out_str << path[path.size() - 1] << " ";

    out_str << "Minimal path: " << dist;

    res = out_str.str();
}



void work_with_web() {
    Net::ServerSocket server(PORT);
    server.set_socket_available_mode();
    
    int pid;

    while ((pid = server.accept_client()) == 0);
    
    Vertex start, end;

    ssize_t size;
    Vertex *vertexes = get_data(server, start, end, size);

    NetworkGraph graph;
    create_graph_from_array(vertexes, size, graph);
    
    IO::print_graph(graph);

    Path path;
    Mass dist = calc_path(path, graph.get_full_graph(), start, end);

    std::cout << dist << std::endl;

    std::string result;
    create_result(result, path, dist);
    char *buff = new char[result.size()];

    for (int i = 0; i < result.size(); i++) buff[i] = result[i]; 
    int ss = result.size();


    send(server.get_client(), buff, result.size(), 0);

    server.close_client();

    while(wait(NULL) != -1);
}



int main() {
    int port;
    std::cout << "Please enter port: ";
    std::cin >> port;
    
    int child_pid = fork();

    if (child_pid == 0) {
        work_with_web();
        return 0;
    }


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
