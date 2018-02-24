#ifndef SYBIL_PROCESS_MANAGER_SYBLING_H
#define SYBIL_PROCESS_MANAGER_SYBLING_H

#include <string>
#include <vector>

namespace sybil {
    class sybling {
    private:
        std::string _path;
        std::vector<std::string> _args;
        pid_t _pid;
        struct process_start_error : std::exception {
            const char* what() const noexcept {return "failed to spawn child";}
        };

        bool _has_args;

        inline void start_error();
        inline void start_success();
        inline void child_routine();

    public:
        //2 possible constructors, path is always required. args can be set later if wished
        sybling(std::string path, std::vector<std::string> args);
        sybling(std::string path);

        void set_args(std::vector<std::string> args);
        void add_args(std::string arg);
        std::vector<std::string> get_args();

        void execute();
    };
}


#endif //SYBIL_PROCESS_MANAGER_SYBLING_H
