#include <vector>


#include "../headers/network.h"

Vertex *create_arr_from_graph(Graph &graph, ssize_t &size) {
    std::vector<Vertex> arr;

    for (Edges now_edges : graph) {
        for (Edge now_edge : now_edges.second) {
            arr.push_back(now_edges.first);
            arr.push_back(now_edge.first);
            arr.push_back(now_edge.second);
        }
    }

    Vertex *ver_array = new Vertex[arr.size()];
    
    size = arr.size();

    for (ssize_t i = 0; i < size; i++) {
        ver_array[i] = std::move(arr[i]);
    }

    return ver_array;
}

void create_graph_from_array(Vertex *ver_graph, ssize_t &size, NetworkGraph &graph) {
    for (int i = 0; i < size; i += 3) {
        graph.add_edge(ver_graph[i], ver_graph[i + 1], ver_graph[i + 2]);
    }
}


