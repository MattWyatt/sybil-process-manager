#include <core/daemon.h>
#include <core/logger.h>
#include <core/exceptions.h>
#include <cli/command_parser.h>
#include <core/locker.h>
#include <core/named_pipe.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <csignal>
#include <thread>

using namespace sybil;

daemon::daemon() {
    logger::get()->debug("about to begin daemon routine...");

    const int pid = fork();

    /* fork error */
    if (pid == -1) {
        throw daemon_start_error();
    }

    /* child process */
    if (pid == 0) {
        logger::get()->debug("beginning daemon watcher routine...");
        daemon_routine();
    }
}

void daemon::create_sybling(std::string name, std::string path) {
    logger::get()->debug({"currently [", std::to_string(_syblings.size()), "] processes in reference"});
    process* p = new process(path);
    sybling* s = new sybling(p);
    _syblings.emplace_back(s);
    _syblings.back()->set_name(name);
    process_logger* pl = new process_logger(_syblings.back());
    _loggers.emplace_back(pl);
}

void daemon::start_sybling(std::string name) {
    logger::get()->debug({"currently [", std::to_string(_syblings.size()), "] processes in reference"});
    for (auto iterator : _syblings) {
        logger::get()->verbose("start looping...");
        logger::get()->verbose({"iterating over [", iterator->get_name(), "]"});
        if (iterator->get_name() == name) {
            logger::get()->debug({"started process [", name, "]"});
            sybling::read_thread(iterator);
            iterator->begin();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            for (auto iterator2 : _loggers) {
                if (iterator2->get_sybling_name() == name) {
                    logger::get()->standard({"starting correspond logger for [", name, "]"});
                    process_logger::start_logger(iterator2);
                }
            }
        }
    }
}

void daemon::terminate_sybling(std::string name) {
    logger::get()->debug({"currently [", std::to_string(_syblings.size()), "] processes in reference"});
    for (auto iterator : _syblings) {
        logger::get()->verbose("terminate looping...");
        logger::get()->verbose({"iterating over [", iterator->get_name(), "]"});
        if (iterator->get_name() == name) {
            logger::get()->standard({"stopped process [", name, "]"});
            iterator->stop();
        }
    }
    for (auto iterator : _loggers) {
        if (iterator->get_sybling_name() == name) {
            iterator->stop_logger();
        }
    }
}

void daemon::send_sybling(std::string name, std::string input) {
    for (auto iterator : _syblings) {
        if (iterator->get_name() == name) {
            logger::get()->standard({"sending [", input, "] to sybling [", name, "]"});
            iterator->write_process(input);
        }
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

    /*
     * for some reason, without these two statements, it won't work
     * i guess it's warming up????
     * don't touch it either way
     */
    create_sybling("/bin/bash", "init");
    start_sybling("init");

    /* begin read loop */
    while (!_exit) {
        std::string command = communicator.read();
        if (command == "quit") {
            communicator.clear_file();
            exit(0);
        }
        logger::get()->debug({"command [", command, "] issued to daemon"});

        /* remove argv[0] and separate the command into a vector  */
        std::string cmd = command_parser::extract_command(command);
        std::vector<std::string> w_cmd = command_parser::split_command(cmd);
        if (w_cmd.at(0) == "new") {
            create_sybling(w_cmd.at(1), w_cmd.at(2));
            logger::get()->standard({"create sybling [", w_cmd.at(1), "]"});
        }
        else if (w_cmd.at(0) == "start") {
            start_sybling(w_cmd.at(1));
            logger::get()->standard({"start sybling [", w_cmd.at(1), "]"});
        }
        else if (w_cmd.at(0) == "stop") {
            terminate_sybling(w_cmd.at(1));
            logger::get()->standard({"terminate sybling [", w_cmd.at(1), "]"});
        }
        else if (w_cmd.at(0) == "send") {
            std::string name = w_cmd.at(1);
            w_cmd.erase(w_cmd.begin(), w_cmd.begin()+2);
            std::string final;
            for (auto iterator : w_cmd) {
                final += iterator;
                final += " ";
            }
            send_sybling(name, final);
        }
    }
}