#include <core/exceptions.h>
#include <core/process.h>
#include <core/logger.h>
#include <unistd.h>
#include <wait.h>
#include <csignal>
#include <cstring>
#include <iostream>

sybil::process::process(const std::function<void()>& function) {
    _function = function;


    int result = fork();
    _pid = result;
    if (result == -1) {
        sybil::log.fatal("error in fork! quitting.");
        return;
    }

    /* child process */
    if (result == 0) {
        /* close I/O so they don't interface with the calling terminal */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        /* redirect I/O to pipes, so the parent can interface */
        if (dup2(_pipe.iread(), STDIN_FILENO) == -1) {
            sybil::log.error("failed to redirect standard input");
            throw "failed to redirect standard input";
        }
        if (dup2(_pipe.owrite(), STDOUT_FILENO) == -1) {
            sybil::log.error("failed to redirect standard output");
            throw "failed to redirect standard output";
        }
        if (dup2(_pipe.owrite(), STDERR_FILENO) == -1) {
            sybil::log.error("failed to redirect standard error");
            throw "failed to redirect standard error";
        }

        /* close all pipes completely. these aren't to be used by the child */
        if (close(_pipe.iread()) == -1 ||
            close(_pipe.iwrite()) == -1 ||
            close(_pipe.oread()) == -1 ||
            close(_pipe.owrite()) == -1) {

            sybil::log.error("failed to close child pipes");
            throw "failed to close child pipes";
        }
        /* execute order 66 */
        sybil::log.debug("starting given process with PID " + std::to_string(_pid));
        _function();
        /* if we don't call exit, the process picks up in the calling function */
        sybil::log.debug("process with PID " + std::to_string(_pid) + " exited");
        exit(0);
    }

    /* parent process */
    if (result > 0) {

        /* no reason to read the input, nor write to the output */
        close(_pipe.iread());
        close(_pipe.owrite());

        /* create the read thread and push it back */
        _reader = std::thread([this]() {
            /* block and read every character from stdin individually
             * then push it back to the output buffer */
            char buffer;
            while (read(_pipe.oread(), &buffer, 1) > 0) {
                _output << buffer;
            }
        });
     }
}

const std::string sybil::process::output() const {
    return _output.str();
}

void sybil::process::write_to(const std::string &input) {
    const char* send = std::string(input + "\n").c_str();
    write(_pipe.iwrite(), send, strlen(send));
}

const pid_t& sybil::process::get_pid() const {
    return _pid;
}

void sybil::process::wait_for_exit() {
    if (_reader.joinable()) {
        _reader.join();
    }
}