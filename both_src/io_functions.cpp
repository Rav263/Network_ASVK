#include <iostream>
#include <fstream>
#include <string>

#include "../headers/network.h"
#include "../headers/logs.h"

namespace IO {
    void print_help() {
        std::cout << "HELP -- print this message" << std::endl;
        std::cout << "V \%vertex\% -- Add vertex to graph" << std::endl;
        std::cout << "E \%vertex\% \%vertex\% \%mass\% -- Add edge to graph" << std::endl;
        std::cout << "PRINT -- print graph" << std::endl;
        std::cout << "SEND -- send graph to server" << std::endl;
    }
    void print_graph(NetworkGraph &graph) {
        std::cout << "Your graph (vertex, vertex, mass)" << std::endl;

        for (Edges now_edges : graph.get_full_graph()) {
            for (Edge now_edge : now_edges.second) {
                std::cout << "(" <<now_edges.first << ", ";
                std::cout << now_edge.first << ", ";
                std::cout << now_edge.second << ")";
                std::cout << std::endl;
            }
        }
    }
    
    void read_graph(NetworkGraph &graph) {
        std::cout << "Please enter HELP to see list of commands" << std::endl;
        std::string now;

        while (true) {
            std::cin >> now;

            if (now.compare("HELP") == 0) {
                print_help();
            } else if (now.compare("V") == 0) {
                Vertex now;
                std::cin >> now;
                graph.add_vertex(now);
            } else if (now.compare("E") == 0) {       
                Vertex start, end;
                Mass mass;
                
                std::cin >> start >> end >> mass;
                graph.add_edge(start, end, mass);
            } else if (now.compare("PRINT") == 0) {
                print_graph(graph);
            } else if (now.compare("SEND") == 0) {
                break;
            }
        }
    }
}
