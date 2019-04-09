#include <map>
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <set>


#include "../headers/network.h"
#include "../headers/logs.h"


void calc_vertex(Vertex vertex, Graph &graph, VertexList &vertexes, std::set<Vertex> used, PathList &paths) {
    for (auto edge : graph[vertex]) {
        if (vertexes.count(edge.first) > 0 && vertexes[edge.first] > vertexes[vertex] + edge.second) {
            vertexes[edge.first] = vertexes[vertex] + edge.second;
            paths[edge.first] = paths[vertex];
            paths[edge.first].push_back(edge.first);
        }
        
        if (vertexes.count(edge.first) == 0) {
            vertexes.insert(Edge(edge.first, vertexes[vertex] + edge.second));
            paths.insert(std::pair<Vertex, Path>(edge.first, paths[vertex]));
            paths[edge.first].push_back(edge.first);
        }
    }
}


void add_vertexes(Vertex now_vertex, VertexList &list, 
        std::set<Vertex> &used, std::set<std::pair<Mass, Vertex>> &queue, 
        Graph &graph, std::set<Vertex> &is_in_queue) {

    for (Edge now_edge : graph[now_vertex]) {
        if (not used.count(now_edge.first) && not is_in_queue.count(now_edge.first)) {
            Mass ver_mass = (not list.count(now_edge.first)) * INT64_MAX;
            ver_mass = ver_mass > 0 ? ver_mass : list[now_edge.first];
            
            queue.insert(std::pair<Mass, Vertex>(ver_mass, now_edge.first));
            is_in_queue.insert(now_edge.first);
        }
    }
}


Mass calc_path(Path &path, Graph &graph, Vertex start, Vertex end) {
    if (start == end) return 0;
    std::set<std::pair<Mass, Vertex>> ver_queue;
    std::set<Vertex> is_in_queue;
    ver_queue.insert(std::pair<Mass, Vertex>(0, start)); 
    
    VertexList vertexes;
    vertexes[start] = 0;
    PathList paths;
    paths[start] = {start};

    std::set<Vertex> used;

    for (auto now_pair : ver_queue) {
        Vertex now_vertex = now_pair.second;
        
        used.insert(now_vertex);
        calc_vertex(now_vertex, graph, vertexes, used, paths);
        
        add_vertexes(now_vertex, vertexes,  used, ver_queue, graph, is_in_queue);
        ver_queue.erase(now_pair);
    }
    path = paths[end];
    if (used.count(end) == 0) return -1;
    return vertexes[end];
}
