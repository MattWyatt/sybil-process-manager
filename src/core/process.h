#ifndef SYBIL_PROCESS_MANAGER_SYBLING_H
#define SYBIL_PROCESS_MANAGER_SYBLING_H

#include <string>
#include <vector>

namespace sybil {
    class process {
    private:
        std::string _path;
        std::vector<std::string> _args;
        std::string _running_command;
        pid_t _pid;


        bool _has_args;
        bool _is_running;

        inline void start_error();
        inline void fork_success();
        inline void terminate_success();
        inline void terminate_failure();
        inline void child_routine();

    public:
        //2 possible constructors, path is always required. args can be set later if wished
        process(std::string path, std::vector<std::string> args);
        process(std::string path);

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
        void terminate();
    };
}


#endif //SYBIL_PROCESS_MANAGER_SYBLING_H
