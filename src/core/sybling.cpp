#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include "sybling.h"

using namespace sybil;

sybling::sybling(std::string path, std::vector<std::string> args) {
    _path = path;
    _args = args;

    _has_args = true;
}

sybling::sybling(std::string path) {
    _path = path;
    _has_args = false;
}

void sybling::set_args(std::vector<std::string> args) {
    _args = args;
    if (!args.empty()) {
        _has_args = true;
        return;
    }
    _has_args = false;
}

void sybling::add_args(std::string arg) {
    _args.push_back(arg);
    _has_args = true;
}

void sybling::execute() {
    auto pid = fork();
    _pid = pid;
    //if everything went wrong, throw an exception
    if (pid == -1) {
        start_error();
    }

    //if we're in the parent process, announce success
    if (pid > 0) {
        start_success();
    }

    //if we're in the child process, execute the child
    if (pid == 0) {
        child_routine();
    }
}

inline void sybling::start_error() {
    std::cerr << "something went wrong starting the process. throwing exception...\n";
    throw sybling::process_start_error();
}

inline void sybling::start_success() {
    std::cout << "successfully spawned child process with id [" << _pid << "]\n";
}

inline void sybling::child_routine() {
    //create C-style types of path and args
    auto p_name = _path.c_str(); //should become char*
    std::vector<char*> v_args; //C-style-character vector for the arguments
    v_args.reserve(_args.size()+1);
    for (auto &iterator : _args) {
        v_args.push_back(const_cast<char*>(iterator.c_str()));
    }
    auto p_args = v_args.data(); //store the raw array in p_args

    std::cout << "[child process] turning over control to given process image...\n";
    std::cout << "process name: " << p_name << std::endl;
    std::string print_args;
    for (int i = 0; i < sizeof(p_args); i++) {
        print_args += p_args[i];
        print_args += " ";
    }
    std::cout << "process arguments: " << print_args << std::endl;
    execvp(p_name, p_args);
}