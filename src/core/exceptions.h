#ifndef SYBIL_PROCESS_MANAGER_EXCEPTIONS_H
#define SYBIL_PROCESS_MANAGER_EXCEPTIONS_H

#include <stdexcept>

namespace sybil {
    class process_start_error : std::exception {
    public:
        virtual const char* what();
    };

    class process_execution_error : std::exception {
    public:
        virtual const char* what();
    };

    class process_termination_error : std::exception {
    public:
        virtual const char* what();
    };

    class daemon_start_error : std::exception {
    public:
        virtual const char* what();
    };

    class daemon_lock_error : std::exception {
    public:
        virtual const char* what();
    };
}


#endif //SYBIL_PROCESS_MANAGER_EXCEPTIONS_H
