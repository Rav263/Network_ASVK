#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

namespace Net {
private:
    int sock;
    struct sockaddr_in sock_addr;
public:
    class ServerSocket {
        ServerSocket(int port) {
            sock = socket(AF_INET, SOCK_STREM, 0);
            
            sock_addr.sin_family = AF_INET;
            sock_addr.sin_addr.s_addr = htons(INADDR_ANY);
            sock_addr.sin_port = htons(port);
        }
    }
}
