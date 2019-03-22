#include <iostream>
#include <string>

#ifndef LOGS_H_
#define LOGS_H_


namespace Logs {
    #define LOG_CONS
    
    void log(const std::string &str);
    void logln(const std::string &str);
}

#endif
