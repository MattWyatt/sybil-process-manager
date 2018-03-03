#include "overseer.h"

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

bool overseer::is_running() {
    return _process->_is_running;
}

int overseer::get_pid() {
    return _process->_pid;
}

std::string overseer::get_running_command() {
    return _process->_running_command;
}