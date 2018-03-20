#ifndef SYBIL_PROCESS_MANAGER_LOGGER_H
#define SYBIL_PROCESS_MANAGER_LOGGER_H

#include <string>
#include <vector>

namespace sybil {
    class logger {
    private:
        logger(){};
        logger(logger const&){};
        logger& operator = (logger const&){};
        int _log_level = 2; //STANDARD by default
        static logger* _logger_instance;

        std::vector<std::string> _prefixes { //list of ordered prefixes so it looks like "[DEBUG] blah blah error"
                "[VERBOSE] ",
                "[DEBUG] ",
                "[STANDARD] ",
                "[FATAL] "
        };

    public:
        //log levels
        enum logger_level {
            VERBOSE = 0,  //literally everything, including print statement debugs
            DEBUG,        //basic debug messages, so errors and such
            STANDARD,     //important output and errors
            FATAL         //anything seriously problematic (crash worthy) will be reported by this
        };

        static logger* get();
        void write(std::string message, logger_level level);
        void verbose(std::string message);
        void debug(std::string message);
        void standard(std::string message);
        void fatal(std::string message);
        void verbose(std::vector<std::string> message);
        void debug(std::vector<std::string> message);
        void standard(std::vector<std::string> message);
        void fatal(std::vector<std::string> message);
        void set_level(logger_level level);
        std::vector<std::string> latest(int count); //return the last X lines in a vector
        std::string print_latest(int count); //print the latest X lines
    };
}


#endif //SYBIL_PROCESS_MANAGER_LOGGER_H
