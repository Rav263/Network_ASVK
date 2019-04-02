#include <iostream>
#include <string>

#include "network.h"
#include "logs.h"

#ifndef IO_HEAD_H_
#define IO_HEAD_H_

namespace IO {
    void print_help();
    void read_graph(NetworkGraph &);
    void print_graph(NetworkGraph &);
}

#endif
