#include <iostream>
#include <string>

#include "../headers/logs.h"

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

    void log_err(const std::string &str) {
#ifdef LOG_ERRS
        std::cerr << str;
#endif
    }

    void logln_err(const std::string &str) {
#ifdef LOG_ERRS
        std::cerr << str << std::endl;
#endif
    }
}
