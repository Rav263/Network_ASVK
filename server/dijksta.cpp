#include <map>
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <set>


#include "../headers/network.h"
#include "../headers/logs.h"


void calc_vertex(Vertex vertex, Graph &graph, std::set<Vertex> &queue, VertexList &vertexes, std::set<Vertex> used) {
    for (auto edge : graph[vertex]) {
        if (used.count(edge.first) > 0) continue;
        if (vertexes.count(edge.first) > 0 && vertexes[edge.first] > vertexes[vertex] + edge.second) {
            vertexes[edge.first] = vertexes[vertex] + edge.second;
        }
        
        if (vertexes.count(edge.first) == 0) {
            vertexes.insert(Edge(edge.first, vertexes[vertex] + edge.second));
        }
        
        queue.insert(edge.first);
    }
}



void calc_path(Path &path, Graph &graph, Vertex start, Vertex end) {
    std::set<Vertex> ver_queue;
    ver_queue.insert(start); 
    
    VertexList vertexes;
    vertexes[start] = 0;

    std::set<Vertex> used;

    for (auto now_vertex : ver_queue) {
        std::cout << now_vertex << std::endl;
        used.insert(now_vertex);
        calc_vertex(now_vertex, graph, ver_queue, vertexes, used);
        ver_queue.erase(now_vertex);

        for (auto shit : vertexes) std::cout << "(" << shit.first << ", " << shit.second << ")" << std::endl;
    }
    
    path.push_back(Edge(end, vertexes[end]));
}
