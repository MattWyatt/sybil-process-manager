#include <core/exceptions.h>
#include <core/logger.h>

const char* sybil::process_start_error::what() {
    sybil::log.error("failed to spawn child");
    return "failed to spawn child";
}

const char* sybil::process_execution_error::what() {
    sybil::log.error("failed to replace running process");
    return "failed to replace running process";
}

const char* sybil::process_termination_error::what() {
    sybil::log.error("failed to terminate process correctly");
    return "failed to terminate process correctly";
}

const char* sybil::daemon_start_error::what() {
    sybil::log.error("failed to start daemon process watcher!");
    return "failed to start daemon process watcher!";
}

const char* sybil::daemon_lock_error::what() {
    sybil::log.error("failed to open the lockfile!");
    return "failed to open the lockfile!";
}