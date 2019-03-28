#include <cstdint>
#include <vector>
#include <utility>
#include <map>

#include "logs.h"

#ifndef NETWORK_H_
#define NETWORK_H_


using Vertex = int64_t;
using Mass = int64_t;
using Edge = std::pair<Vertex, Mass>;
using Edges = std::pair<Vertex, std::map<Vertex, Mass>>;
using Graph = std::map<Vertex, std::map<Vertex, Mass>>;
using Path = std::vector<Edge>;
using VertexList = std::map<Vertex, Mass>;
using Queue = std::queue<Vertex>;

class NetworkGraph {
private:
    Graph graph;
public:
    void add_vertex(Vertex now) {
        graph.insert(Edges(now, {}));
    }

    void add_edge(Vertex begin, Vertex end, Mass mass) {
        if (graph.count(begin) < 0) {
            add_vertex(begin);
        }
        graph[begin].insert(Edge(end, mass));

        if (graph.count(end) < 0) {
            add_vertex(end);
        }
        graph[end].insert(Edge(begin,mass));
    }

    std::map<Vertex, Mass> &get_vertex_edges(Vertex now) {
        if (graph.count(now) < 0) {
            Logs::logln_err("NO ELEMENT");
            throw 1;
        }

        return graph[now];
    }

    Graph &get_full_graph() {
        return graph;
    }

    bool is_in_graph(Vertex now) {
        return graph.count(now) > 0;
    }

    bool is_edge(Vertex beg, Vertex end) {
        if (is_in_graph(beg)) {
            return graph[beg].count(end) > 0;
        }

        return false;
    }
};

#endif
