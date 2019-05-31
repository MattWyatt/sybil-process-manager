#ifndef SYBIL_PROCESS_MANAGER_DAEMON_H
#define SYBIL_PROCESS_MANAGER_DAEMON_H

namespace sybil {
    bool start_daemon();

    bool stop_daemon();

    bool daemon_is_running();
}

#endif //SYBIL_PROCESS_MANAGER_DAEMON_H
