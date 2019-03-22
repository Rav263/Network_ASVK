#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "logs.h"

#ifndef SOCKET_H_
#define SOCKET_H_

namespace Net {
    class ServerSocket {
    private:
        int sock;
        struct sockaddr_in sock_addr;
    
    public:
        ServerSocket(int port) {
            Logs::log("Starting server.. ");
            sock = socket(AF_INET, SOCK_STREAM, 0);
            
            sock_addr.sin_family = AF_INET;
            sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
            sock_addr.sin_port = htons(port);
        }

        int get_socket() const {
            return sock;
        }

        const struct sockaddr_in *get_sock_addr() const {
            return &sock_addr;
        }

        size_t get_sock_addr_size() {
            return sizeof(sock_addr);
        }

        ~ServerSocket() {
            close(sock);
        }
    };
}

#endif
