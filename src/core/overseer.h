#ifndef SYBIL_PROCESS_MANAGER_OVERSEER_H
#define SYBIL_PROCESS_MANAGER_OVERSEER_H

#include "process.h"

namespace sybil {
    class overseer  {
    private:
        sybil::process* _process;

    public:
        overseer(sybil::process* process);
        overseer(std::string path);
        overseer(std::string path, std::vector<std::string> args);

        void begin();
        void stop();

        //duplicated functions from the friend process
        bool is_running();
        pid_t get_pid();
        std::string get_running_command();
    };
}


#endif //SYBIL_PROCESS_MANAGER_OVERSEER_H
