#ifndef SYBIL_PROCESS_MANAGER_SYBLING_H
#define SYBIL_PROCESS_MANAGER_SYBLING_H

#include <string>
#include <vector>

namespace sybil {
    class sybling {
    private:
        std::string _path;
        std::vector<std::string> _args;
        std::string _running_command;
        pid_t _pid;

        //TODO: move these exceptions into an "exceptions.h/exceptions.cpp" file
        struct process_start_error : std::exception {
            const char* what() const noexcept {return "failed to spawn child";}
        };
        struct execution_error : std::exception {
            const char* what() const noexcept {return "failed to replace running process";}
        };

        bool _has_args;
        bool _is_running;

        inline void start_error();
        inline void fork_success();
        inline void child_routine();

    public:
        //2 possible constructors, path is always required. args can be set later if wished
        sybling(std::string path, std::vector<std::string> args);
        sybling(std::string path);

        //argument manipulation functions
        void set_args(std::vector<std::string> args);
        void add_args(std::string arg);
        std::vector<std::string> get_args();

        //utility functions for getting basic information
        bool is_running();
        bool is_child();
        pid_t get_pid();
        std::string get_running_command();

        void execute();
    };
}


#endif //SYBIL_PROCESS_MANAGER_SYBLING_H
