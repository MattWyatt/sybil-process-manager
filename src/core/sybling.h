#ifndef SYBIL_PROCESS_MANAGER_OVERSEER_H
#define SYBIL_PROCESS_MANAGER_OVERSEER_H

#include <core/process.h>
#include <atomic>

namespace sybil {
    class sybling  {
    private:
        sybil::process* _process;
        std::string _name;
        std::atomic<char*> _stdout;

    public:
        sybling(sybil::process* process);
        sybling(std::string path);
        sybling(std::string path, std::vector<std::string> args);

        void begin();
        void stop();
        void set_name(std::string name);
        std::string get_name();
        std::string read_process();
        std::string get_output();
        void write_process(std::string message);
        static void read_thread(sybling* o);

        //duplicated functions from the friend process
        bool is_running();
        pid_t get_pid();
        std::string get_running_command();
    };
}


#endif //SYBIL_PROCESS_MANAGER_OVERSEER_H
