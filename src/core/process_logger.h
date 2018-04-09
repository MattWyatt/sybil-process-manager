/*
 * class attached to a sybling to log the process to a logfile
 * this is separate from the actual sybling to isolate the name getting functions
 */

#ifndef SYBIL_PROCESS_MANAGER_PROCESS_LOGGER_H
#define SYBIL_PROCESS_MANAGER_PROCESS_LOGGER_H

#include <core/sybling.h>

using namespace sybil;

namespace sybil {
    class process_logger {
    private:
        sybling* _sybling_ptr;
        bool _quit_logging;
        std::string _name;
        std::string _path;
        void _writer();

    public:
        process_logger(sybling* sybling_ptr);

        /*
         * will return false if it fails to start
         * the only reason it could fail to start is if the read thread isn't running
         */
        static bool start_logger(process_logger* pl);
        std::string get_name();
        std::string get_path();
        void stop_logger();
    };
}


#endif //SYBIL_PROCESS_MANAGER_PROCESS_LOGGER_H
