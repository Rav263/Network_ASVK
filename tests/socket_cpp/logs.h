#include <iostream>
#include <string>

#ifndef LOGS_H_
#define LOGS_H_


namespace Logs {
    #define LOG_CONS
    #define LOG_ERRS

    void log(const std::string &str);
    void logln(const std::string &str);
    void log_err(const std::string &str);
    void logln_err(const std::string &str);
}

#endif
