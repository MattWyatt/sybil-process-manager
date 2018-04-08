#include <core/sybling.h>
#include <core/logger.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>

using namespace sybil;

sybling::sybling(process* process) {
    _process = process;
}

sybling::sybling(std::string path) {
    process* p = new process(path);
    _process = p;
}

sybling::sybling(std::string path, std::vector<std::string> args) {
    process* p = new process(path, args);
    _process = p;
}

void sybling::begin() {
    _process->execute();
}

void sybling::stop() {
    _process->terminate();
}

void sybling::set_name(std::string name) {
    _name = name;
}

std::string sybling::get_name() {
    return _name;
}

std::string sybling::read_process() {
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

std::string sybling::get_output() {
    return std::string(_stdout.load(std::memory_order_seq_cst));
}

void sybling::write_process(std::string message) {
    std::string send = message;
    send += "\n\r";
    logger::get()->debug(send);
    write(_process->_pipe->get_stdin()[PIPE_WRITE], send.c_str(), strlen(send.c_str()));
}

/*
 * listen for whatever reason this works, so don't touch it.
 * if you pass the sybling as a reference, instead of as the object itself,
 * then nothing gets deleted
 */
void sybling::read_thread(sybling* o) {
    std::thread reader(&sybling::read_process, o);
    reader.detach();
}

bool sybling::is_running() {
    return _process->_is_running;
}

int sybling::get_pid() {
    return _process->_pid;
}

std::string sybling::get_running_command() {
    return _process->_running_command;
}