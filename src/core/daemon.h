/*
 * class that will be instanced to keep track of processes
 * sybil itself will, upon startup, check whether or not this daemon is running
 * if the daemon is not running it will be started, otherwise sybil will send commands directly to it
 */

#ifndef SYBIL_PROCESS_MANAGER_DAEMON_H
#define SYBIL_PROCESS_MANAGER_DAEMON_H

#include <core/sybling.h>
#include <core/process_logger.h>
#include <vector>

namespace sybil {
    class daemon {
    private:
        bool _exit = false;
        std::vector<sybil::sybling*> _syblings;
        std::vector<sybil::process_logger*> _loggers;
        inline void daemon_routine();

    protected:
        void create_sybling(std::string path, std::string name);
        void start_sybling(std::string name);
        void terminate_sybling(std::string name);

    public:
        daemon();
    };
}


#endif //SYBIL_PROCESS_MANAGER_DAEMON_H
