#ifndef SYBIL_PROCESS_MANAGER_OVERSEER_H
#define SYBIL_PROCESS_MANAGER_OVERSEER_H

#include <core/process.h>
#include <atomic>

namespace sybil {
    class overseer  {
    private:
        sybil::process* _process;
        std::atomic<char*> _stdout;

    public:
        overseer(sybil::process* process);
        overseer(std::string path);
        overseer(std::string path, std::vector<std::string> args);

        void begin();
        void stop();
        std::string read_process();
        std::string get_output();
        void write_process(std::string message);
        static void read_thread(overseer* o);

        //duplicated functions from the friend process
        bool is_running();
        pid_t get_pid();
        std::string get_running_command();
    };
}


#endif //SYBIL_PROCESS_MANAGER_OVERSEER_H
