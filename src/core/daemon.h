/*
 * class that will be instanced to keep track of processes
 * sybil itself will, upon startup, check whether or not this daemon is running
 * if the daemon is not running it will be started, otherwise sybil will send commands directly to it
 */

#ifndef SYBIL_PROCESS_MANAGER_DAEMON_H
#define SYBIL_PROCESS_MANAGER_DAEMON_H

#include <core/sybling.h>
#include <vector>

class daemon {
private:
    bool _exit = false;
    std::vector<sybil::sybling> _syblings;
    inline void daemon_routine();

protected:
    void create_sybling();
    void terminate_sybling();

public:
    daemon();
};


#endif //SYBIL_PROCESS_MANAGER_DAEMON_H
