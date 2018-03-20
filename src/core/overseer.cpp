#include "overseer.h"
#include "logger.h"
#include <unistd.h>
#include <iostream>
#include <cstring>

using namespace sybil;

overseer::overseer(process* process) {
    _process = process;
}

overseer::overseer(std::string path) {
    process* p = new process(path);
    _process = p;
}

overseer::overseer(std::string path, std::vector<std::string> args) {
    process* p = new process(path, args);
    _process = p;
}

void overseer::begin() {
    _process->execute();
}

void overseer::stop() {
    _process->terminate();
}

std::string overseer::read_process() {
    std::string t;
    char cChar;
    int result;
    while(true) {
        result = read(_process->_pipe->get_stdout()[PIPE_READ], &cChar, 1);
        if (result != 1) {
            break;
        }
        logger::get()->verbose(std::to_string(cChar));
        t += cChar;
    }
    logger::get()->standard(t);
    return "H";
}

void overseer::write_process(std::string message) {
    write(_process->_pipe->get_stdin()[PIPE_WRITE], message.c_str(), strlen(message.c_str()));
}

bool overseer::is_running() {
    return _process->_is_running;
}

int overseer::get_pid() {
    return _process->_pid;
}

std::string overseer::get_running_command() {
    return _process->_running_command;
}