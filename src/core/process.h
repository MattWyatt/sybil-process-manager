#ifndef SYBIL_PROCESS_MANAGER_SYBLING_H
#define SYBIL_PROCESS_MANAGER_SYBLING_H

#include "process_pipe.h"
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <functional>

namespace sybil {

    class process {
    private:
        std::thread _reader;

        process_pipe _pipe;

        std::stringstream _output;

        std::function<void(void)> _function;

        pid_t _pid;

    public:
        explicit process(const std::function<void()>& _function);

        const std::string output() const;

        void write_to(const std::string &input);

        const pid_t& get_pid() const;

        void wait_for_exit();
    };
}


#endif //SYBIL_PROCESS_MANAGER_SYBLING_H
