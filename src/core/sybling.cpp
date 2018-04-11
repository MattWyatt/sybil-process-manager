#include <core/sybling.h>
#include <core/logger.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <wait.h>

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

void sybling::wait_for_exit() {
    int status_ptr;
    waitpid(_process->get_pid(), &status_ptr, 0);
}

bool sybling::is_stopped() {
    return !is_running();
}

void sybling::set_name(std::string name) {
    _name = name;
}

std::string sybling::get_name() {
    return _name;
}

/*
 * blocking call that retrieves all output of a process
 */
void sybling::read_process() {
    logger::get()->verbose("read_process() called");
    std::string process_output;
    char cChar;
    int result;

    /*
     * read character by character and store it in process_output
     * each time the output is updated, store it in _stdout
     */
    while(true) {
        result = read(_process->_pipe->get_stdout()[PIPE_READ], &cChar, 1);
        if (result != 1) {
            logger::get()->debug("no output left in process!");
            break;
        }
        process_output += cChar;
        _stdout += cChar;
        logger::get()->verbose({"_stdout: ", _stdout});
    }
}

std::string sybling::get_output() {
    return _stdout;
}

void sybling::write_process(std::string message) {
    std::string send = message;
    send += "\n";
    logger::get()->debug(send);
    write(_process->_pipe->get_stdin()[PIPE_WRITE], send.c_str(), strlen(send.c_str()));
}

bool sybling::is_reading() {
    return _read_thread_running;
}

/*
 * listen for whatever reason this works, so don't touch it.
 * if you pass the sybling as a reference, instead of as the object itself,
 * then nothing gets deleted
 */
void sybling::read_thread(sybling* o) {
    std::thread reader(&sybling::read_process, o);
    reader.detach();
    o->_read_thread_running = true;
}

bool sybling::is_running() {
    while(waitpid(-1, nullptr, WNOHANG) > 0) {
        // Wait for defunct....
    }

    if (0 == kill(_process->get_pid(), 0))
        return true; // Process exists

    return false;
}

int sybling::get_pid() {
    return _process->_pid;
}

std::string sybling::get_running_command() {
    return _process->_running_command;
}