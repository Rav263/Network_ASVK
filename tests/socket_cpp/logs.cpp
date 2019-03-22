#include <iostream>
#include <string>

#include "logs.h"

namespace Logs {
    void logln(const std::string &str) {
#ifdef LOG_CONS
        std::cout << str << std::endl;
#endif
    }
    void log(const std::string &str) {
#ifdef LOG_CONS
        std::cout << str;
#endif
    }
}
