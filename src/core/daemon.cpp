#include <csignal>

#include <unistd.h>
#include <sys/stat.h>

#include "core/daemon.h"
#include "core/exceptions.h"
#include "core/locker.h"
#include "core/logger.h"


bool sybil::start_daemon() {
    const int pid = fork();

    if (pid == -1) {
        throw daemon_start_error();
    }

    if (pid == 0) {
        sybil::log.info("beginning daemon routine");

        /* new file perms and process group */
        umask(0);
        setsid();

        /* close any and all open file descriptors */
        for (int i = getdtablesize(); i >= 0; i--) {
            close(i);
        }

        /* change to root dir to prevent blocking any mount calls */
        chdir("/");

        /*
         * create a locker on /tmp/sybil.pid
         * check to see if it is locked
         * if it is, then exit because that means a daemon is already running
         */
        locker pid_file("/tmp/sybil.pid");
        if (pid_file.was_already_locked()) {
            exit(0);
        }

        /* write process id to the pid file for future reference */
        std::ofstream pid_file_writer("/tmp/sybil.pid");
        if (pid_file_writer.is_open()) {
            pid_file_writer << getpid();
            pid_file_writer.close();
        }

        /* ignore any disconnection from a terminal */
        signal(SIGHUP, SIG_IGN);

        sybil::log.info("daemon started successfully");
    }
}