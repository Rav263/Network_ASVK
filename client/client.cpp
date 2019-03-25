#include <string>

#include "../headers/sockets.h"
#include "../headers/logs.h"


enum {
    PORT_NUM = 2917,
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Logs::logln_err("NO_IP");
        return 1;
    }

    Net::ClientSocket *client = new Net::ClientSocket(PORT_NUM, std::string(argv[1]));
    client->connect_to_server();

    delete client;
}
