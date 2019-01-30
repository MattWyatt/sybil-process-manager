#ifndef SYBIL_PROCESS_MANAGER_SYBLING_H
#define SYBIL_PROCESS_MANAGER_SYBLING_H

#include <core/process_pipe.h>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <functional>

namespace sybil {

    class process {
    private:
        static std::vector<std::thread> _readers;

        process_pipe _pipe;

        std::stringstream _output;

        std::function<void(void)> _function;

        pid_t _pid;

    public:
        static void exit_processes();

        explicit process(const std::function<void()> &_function);

        void execute();

        const std::string output() const;

        void write_to(const std::string &input);

        const pid_t& get_pid() const;

    };
}


#endif //SYBIL_PROCESS_MANAGER_SYBLING_H
