#include <map>
#include <utility>
#include <string>
#include <sys/socket.h>
#include <vector>
#include <iostream>

#include "../headers/logs.h"
#include "../headers/network.h"

namespace Net {
    template<typename T>
    void send_buffer(int socket, const T *buffer, ssize_t len) {
        ssize_t writed = 0;
        while(writed != len) {
            ssize_t tmp = send(socket, (char *)buffer + writed, len - writed, 0);
            
            if (tmp <= 0) throw 1;
            writed += tmp;
        }
    }

    void send_string(std::string &mess, int socket) {
        int64_t len = mess.size();

        send_buffer(socket, mess.c_str(), len);
    }

    void send_array(Vertex *graph, ssize_t len, int socket) { 
        send_buffer(socket, graph, len * sizeof(*graph));
    }

    void send_vertex(Vertex *ver, int socket) {
        send_buffer(socket, ver, sizeof(*ver));
    }

    template<typename T>
    void recv_buffer(int socket, T *buffer, ssize_t len) {
        ssize_t readed = 0;

        while (readed != len) {
            ssize_t tmp = recv(socket, (char *)buffer + readed, len - readed, 0);
            
            if (tmp <= 0) throw 1;
            readed += tmp;
        }
    }

    void recv_vertex(Vertex *ver, int socket) {
        recv_buffer(socket, ver, sizeof(*ver));
    }

    void recv_array(Vertex *graph, ssize_t len, int socket) {
        recv_buffer(socket, graph, len * sizeof(*graph));
    }
}
