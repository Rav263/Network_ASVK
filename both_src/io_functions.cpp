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
        std::cout << "DIST -- minimal distance between vertices" << std::endl;
        std::cout << "PATH -- minimal path between vertices" << std::endl;
        std::cout << "EXIT -- end work with server" << std::endl;
        std::cout << "FILE -- read graph from file" << std::endl;
    }
    void print_graph(NetworkGraph &graph) {
        std::cout << "Your graph (vertex, vertex, mass)" << std::endl;

        for (Edges now_edges : graph.get_full_graph()) {
            for (Edge now_edge : now_edges.second) {
                std::cout << "(" << now_edges.first << ", ";
                std::cout << now_edge.first << ", ";
                std::cout << now_edge.second << ")";
                std::cout << std::endl;
            }
        }

        for (int i = 0; i <= 15; i++) {
            if (not graph.is_in_graph(i)) continue;

            auto now_edges = graph.get_vertex_edges(i);

            for (int k = 0; k <= 15; k++) {
                if (not graph.is_in_graph(k)) continue;
                if (now_edges.count(k) == 0) std::cout << "0 ";
                else std::cout << now_edges[k] << " ";
            }
            std::cout << std::endl;
        }
    }
    void read_graph_from_file(NetworkGraph &graph, std::ifstream &file) {
        Vertex start, end;
        Mass mass;

        while (file >> start >> end >> mass){
            graph.add_edge(start, end, mass);
        }

        print_graph(graph);
    }

    int read_graph(NetworkGraph &graph) {
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
            } else if (now.compare("DIST") == 0) {
                return 0;
            } else if (now.compare("PATH") == 0) {
                return 1;
            } else if (now.compare("EXIT") == 0) {
                return -1;
            } else if (now.compare("FILE") == 0) {
                std::cout << "please enter file name: ";
                std::string file_name;
                std::cin >> file_name;

                std::ifstream file(file_name);

                read_graph_from_file(graph, file);
            }
        }

        return 3;
    }
}
