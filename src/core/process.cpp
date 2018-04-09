#include <core/exceptions.h>
#include <core/process.h>
#include <core/logger.h>
#include <unistd.h>
#include <wait.h>
#include <csignal>
#include <iostream>

using namespace sybil;

process::process(std::string path, std::vector<std::string> args) {
    _path = path;
    _args = args;
    _pipe = new process_pipe();

    _has_args = true;
}

process::process(std::string path) {
    _path = path;
    _has_args = false;
    _pipe = new process_pipe();
}

void process::set_args(std::vector<std::string> args) {
    _args = args;
    if (!args.empty()) {
        _has_args = true;
        return;
    }
    _has_args = false;
}

void process::add_args(std::string arg) {
    _args.push_back(arg);
    _has_args = true;
}

std::vector<std::string> process::get_args() {
    return _args;
}

bool process::is_running() {
    if (kill(_pid, 0) == 0 && _is_running) {
        _is_running = false;
    }
    return _is_running;
}

bool process::is_child() {
    if (_pid == 0) {
        return true;
    }
    return false;
}

pid_t process::get_pid() {
    return _pid;
}

std::string process::get_running_command() {
    return _running_command;
}

void process::execute() {
    _pid = fork();
    /* if everything went wrong, throw an exception */
    if (_pid == -1) {
        start_error();
    }

    /* if we're in the parent process, announce success and set full command */
    if (_pid > 0) {
        parent_routine();
        fork_success();
    }

    /* if we're in the child process, execute the child */
    if (is_child()) {
        _pid = getpid();
        child_routine();
    }
}

void process::terminate() {
    kill(_pid, SIGKILL);

    int process_status;
    const auto waited = waitpid(_pid, &process_status, 0);
    if (waited == _pid) {
        if (WIFEXITED(process_status) == -1) {
            terminate_failure();
        }
        else {
            terminate_success();
        }
    }
    else {
        terminate_failure();
    }
}

inline void process::start_error() {
    logger::get()->fatal("something went wrong starting the process. throwing exception...");
    throw sybil::process_start_error();
}

inline void process::fork_success() {
    logger::get()->debug("successfully forked child process");
}

inline void process::terminate_success() {
    logger::get()->debug("successfully stopped child process");
}

inline void process::terminate_failure() {
    logger::get()->fatal("something went wrong when stopping the process. throwing exception...");
    throw sybil::process_termination_error();
}

inline void process::parent_routine() {
    _is_running = true;
    //close in[read] and out[write]
    close(_pipe->get_stdin()[PIPE_READ]);
    close(_pipe->get_stdout()[PIPE_WRITE]);
    std::string buffer;
    buffer += _path;
    for (auto arg : _args) {
        buffer += " ";
        buffer += arg;
    }
    _running_command = buffer;
}

inline void process::child_routine() {
    /* redirect the input and output through pipes to the parent process */
    if (dup2(_pipe->get_stdin()[PIPE_READ], STDIN_FILENO) == -1) {
        logger::get()->fatal("failed to redirect standard input!");
    }
    if (dup2(_pipe->get_stdout()[PIPE_WRITE], STDOUT_FILENO) == -1) {
        logger::get()->fatal("failed to redirect standard output!");
    }
    if (dup2(_pipe->get_stdout()[PIPE_WRITE], STDERR_FILENO) == -1) {
        logger::get()->fatal("failed to redirect standard error output!");
    }
    //close all pipes to the child process, they're only to be accessed by the sybling
    if (close(_pipe->get_stdin()[PIPE_READ]) == -1 ||
    close(_pipe->get_stdin()[PIPE_WRITE]) == -1 ||
    close(_pipe->get_stdout()[PIPE_READ]) == -1 ||
    close(_pipe->get_stdout()[PIPE_WRITE]) == -1) {
        logger::get()->fatal("failed to close child pipes!");
    }


    //create C-style types of path and args
    auto p_name = _path.c_str(); //should become char*

    std::cout << "[child process] attempting to turn over control to given process image...\n";
    if (_has_args) { //run execvp if there are arguments to be run with the program
        std::vector<char*> v_args; //C-style-character vector for the arguments
        v_args.reserve(_args.size());
        for (auto &iterator : _args) {
            v_args.push_back(const_cast<char*>(iterator.c_str()));
        }
        v_args.push_back(nullptr);
        auto p_args = v_args.data(); //store the raw array in p_args
        _is_running = true;
        auto result = execvp(p_name, p_args);
        if (result < 0) {
            logger::get()->write("execvp execution error", logger::DEBUG);
            throw sybil::process_execution_error();
        }
        else {
            if (close(_pipe->get_stdin()[PIPE_READ]) == -1 ||
                close(_pipe->get_stdin()[PIPE_WRITE]) == -1 ||
                close(_pipe->get_stdout()[PIPE_READ]) == -1 ||
                close(_pipe->get_stdout()[PIPE_WRITE]) == -1) {
                logger::get()->fatal("failed to close child pipes!");
            }
        }
        logger::get()->verbose("closed child pipes!");
    }
    else { //if no arguments, just run execl
        _is_running = true;
        if (execl(p_name, nullptr) < 0) {
            logger::get()->debug("execl execution error");
            throw sybil::process_execution_error();
        }
        else {
            if (close(_pipe->get_stdin()[PIPE_READ]) == -1 ||
                close(_pipe->get_stdin()[PIPE_WRITE]) == -1 ||
                close(_pipe->get_stdout()[PIPE_READ]) == -1 ||
                close(_pipe->get_stdout()[PIPE_WRITE]) == -1) {
                logger::get()->fatal("failed to close child pipes!");
            }
            logger::get()->verbose("closed child pipes!");
        }
    }
}