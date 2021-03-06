/*
 * list of fatal exceptions
 * any of these, if thrown, will terminate the process
 */

#ifndef SYBIL_PROCESS_MANAGER_EXCEPTIONS_H
#define SYBIL_PROCESS_MANAGER_EXCEPTIONS_H

#include <stdexcept>

namespace sybil {
    class process_start_error : std::exception {
    public:
        const char* what();
    };

    class process_execution_error : std::exception {
    public:
        const char* what();
    };

    class process_termination_error : std::exception {
    public:
        const char* what();
    };

    class daemon_start_error : std::exception {
    public:
        const char* what();
    };

    class daemon_lock_error : std::exception {
    public:
        const char* what();
    };
}


#endif //SYBIL_PROCESS_MANAGER_EXCEPTIONS_H
