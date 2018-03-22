#include <core/overseer.h>
#include <core/logger.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>

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
    std::string process_output = "";
    char cChar;
    int result;
    while(true) {
        result = read(_process->_pipe->get_stdout()[PIPE_READ], &cChar, 1);
        if (result != 1) {
            break;
        }
        logger::get()->verbose(std::to_string(cChar));
        process_output += cChar;
        _stdout.store((char*)process_output.c_str(), std::memory_order_seq_cst);
    }
    return process_output;
}

std::string overseer::get_output() {
    return std::string(_stdout.load(std::memory_order_seq_cst));
}

void overseer::write_process(std::string message) {
    std::string send = message;
    send += "\n\r";
    logger::get()->debug(send);
    write(_process->_pipe->get_stdin()[PIPE_WRITE], send.c_str(), strlen(send.c_str()));
}

/*
 * listen for whatever reason this works, so don't touch it.
 * if you pass the overseer as a reference, instead of as the object itself,
 * then nothing gets deleted
 */
void overseer::read_thread(overseer* o) {
    std::thread reader(&overseer::read_process, o);
    reader.detach();
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