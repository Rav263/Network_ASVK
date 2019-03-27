#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <map>
#include <utility>
#include "logs.h"
#include "network.h"


#ifndef SOCKET_H_
#define SOCKET_H_

namespace Net {
    void send_buffer(int socket, const void *buffer, ssize_t len) {
        ssize_t writed = 0;
        while(writed != len) {
            ssize_t tmp = send(socket, buffer + writed, len, 0);
            
            if (tmp < 0) throw 1;
            writed += tmp;
        }
    }

    void send_string(std::string &mess, int socket) {
        int64_t len = mess.size();

        send_buffer(socket, mess.c_str(), len);
    }

    void send_array(Vertex *graph, ssize_t len, int socket) { 
        send_buffer(socket, graph, len);
    }


    void recv_buffer(int socket, void **buffer, ssize_t len) {
        ssize_t readed = 0;

        while (readed != len) {
            ssize_t tmp = recv(socket, buffer+readed
        }
    }

    class ServerSocket {
    private:
        int sock;
        struct sockaddr_in sock_addr;
        int client;
        socklen_t size;

    public:
        ServerSocket(int port) {
            Logs::log("Creating socket.. ");
            this->sock = socket(AF_INET, SOCK_STREAM, 0);
            
            if (sock < 0) {
                Logs::logln("Falied");
                throw 1;
            }

            Logs::logln("Successfull");


            this->sock_addr.sin_family = AF_INET;
            this->sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
            this->sock_addr.sin_port = htons(port);
            
            Logs::log("Starting server.. ");
            if (bind(this->sock, (const sockaddr *) &(this->sock_addr), sizeof(this->sock_addr)) < 0) {
                Logs::logln("Falied");
                throw 1;
            }
            Logs::logln("Successfull");
            this->client = -1;

            this->size = sizeof(this->sock_addr);
        }

        int get_socket() const {
            return this->sock;
        }

        const struct sockaddr_in *get_sock_addr() const {
            return &(this->sock_addr);
        }

        size_t get_sock_addr_size() const {
            return this->size;
        }
    
        void set_socket_available_mode() const {
            Logs::log("Setting up connecting mode.. ");
            if (listen(this->sock, 1) < 0) {
                Logs::logln_err("Falied");
                throw 1;
            }

            Logs::logln("Successfull");
        }

        void accept_client() {
            Logs::log("Connecting to client.. ");
            
            this->client = accept(this->sock, (struct sockaddr *) &(this->sock_addr), &(this->size));

            if (this->client < 0) {
                Logs::logln_err("Falied");
                throw 1;
            }

            Logs::logln("Successfull");
        }

        void close_client() { 
            if (this->client > 0) close(this->client);
            this->client = -1;
        }

        int get_client() {
            return this->client;
        }        

        ~ServerSocket() {
            close(this->sock);
            if (this->client > 0) close(this->client);
        }
    };

    class ClientSocket {
    private:
        int sock;
        struct sockaddr_in sock_addr;
    public:
        ClientSocket(int port, const std::string &ip) {
            Logs::log("Creating socket.. ");
            this->sock = socket(AF_INET, SOCK_STREAM, 0);

            if (sock < 0) {
                Logs::logln("Falied");
                throw 1;
            }
            Logs::logln("Successfull");
            
            this->sock_addr.sin_addr.s_addr = inet_addr(ip.c_str());
            this->sock_addr.sin_family = AF_INET;
            this->sock_addr.sin_port = htons(port);
        }

        void connect_to_server() {
            Logs::log("Connecting.. ");
            if (connect(this->sock, (const sockaddr *) &(this->sock_addr), sizeof(this->sock_addr)) < 0) {
                Logs::logln("Falied");
                throw 1;
            }

            Logs::logln("Successfull");
        }

        int get_socket() const {
            return this->sock;
        }

        const struct sockaddr_in *get_sock_addr() const {
            return &(this->sock_addr);
        }

        size_t get_sock_addr_size() const {
            return sizeof(this->sock_addr);
        }

        ~ClientSocket() {
            close(this->sock);
        }
    };
}

#endif
