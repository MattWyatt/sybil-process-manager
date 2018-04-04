#include <core/daemon.h>
#include <core/logger.h>
#include <core/exceptions.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <iostream>

using namespace sybil;

daemon::daemon() {
    logger::get()->debug("about to begin daemon routine...");

    const int pid = fork();

    // error
    if (pid == -1) {
        throw daemon_start_error();
    }

    // parent routine
    if (pid > 0) {
        logger::get()->debug("successfully spawned daemon watcher!");
        exit(0);
    }

    // child routine
    if (pid == 0) {
        logger::get()->debug("beginning daemon watcher routine...");
        daemon_routine();
    }
}

inline void daemon::daemon_routine() {

    // new process group
    setsid();

    // close any and all open file descriptors
    for (int i = getdtablesize(); i >= 0; i--) {
        close(i);
    }

    // new file perms
    umask(0);

    // change to root dir to prevent blocking any mount calls
    chdir("/");

    // check to see if daemon is already running
    int pid_file = open("/tmp/sybil.pid", O_CREAT | O_RDWR, 0666);
    int lock = flock(pid_file, LOCK_EX | LOCK_NB);
    logger::get()->debug({"flock() returned: ", std::to_string(lock)});
    if (lock) {
        if (EWOULDBLOCK == errno || EBADF == errno) {
            // daemon already started so just exit
            logger::get()->debug("daemon already running, exiting...");
            exit(0);
        }
    }


    logger::get()->debug("started daemon process successfully");
    // add handling so that we can listen for messages
}