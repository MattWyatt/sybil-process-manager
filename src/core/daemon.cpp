#include <core/daemon.h>
#include <core/logger.h>
#include <core/exceptions.h>
#include <core/locker.h>
#include <core/named_pipe.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <csignal>

using namespace sybil;

daemon::daemon() {
    logger::get()->debug("about to begin daemon routine...");

    const int pid = fork();

    /* fork error */
    if (pid == -1) {
        throw daemon_start_error();
    }

    /* parent process */
    if (pid > 0) {
        logger::get()->debug({"successfully spawned daemon watcher! id: [", std::to_string(pid), "]"});
        exit(0);
    }

    /* child process */
    if (pid == 0) {
        logger::get()->debug("beginning daemon watcher routine...");
        daemon_routine();
    }
}

inline void daemon::daemon_routine() {
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
    if (pid_file.is_locked()) {
        exit(0);
    }

    /* write process id to the pid file for future reference */
    std::ofstream pid_file_writer("/tmp/sybil.pid");
    if (pid_file_writer.is_open()) {
        pid_file_writer << getpid();
        pid_file_writer.close();
        logger::get()->debug({"wrote pid [", std::to_string(getpid()), "] to pid file"});
    }

    /* ignore any disconnection from a terminal */
    signal(SIGHUP, SIG_IGN);


    logger::get()->debug("started daemon process successfully");

    /* create named pipe before we setsid() and umask() */
    named_pipe communicator("/tmp/sybil.pipe");

    /* begin read loop */
    while (!_exit) {
        std::string command = communicator.read();
        if (command == "quit") {
            exit(0);
        }
        logger::get()->debug({"command [", command, "] issued to daemon"});
        _parse_and_handle(command);
    }
}