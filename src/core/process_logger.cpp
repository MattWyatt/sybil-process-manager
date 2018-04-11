#include <core/process_logger.h>
#include <thread>
#include <fstream>
#include "logger.h"

using namespace sybil;

process_logger::process_logger(sybling* sybling_ptr) {
    _sybling_ptr = sybling_ptr;
    _sybling_ptr->get_name();
}

void process_logger::_writer() {
    logger::get()->debug("logfile writer process started!");
    std::string log_path = get_path();
    std::ofstream log_file;

    /*
     * go ahead and create the logfile
     */
    log_file.open(log_path, std::ios::out | std::ios::trunc);
    log_file << "";
    log_file.close();

    while (!_quit_logging) {

        /* truncate the entire file each time. this should be optimized later */
        std::string output = _sybling_ptr->get_output();
        if (!output.empty()) {
            logger::get()->verbose("found output, writing it to file!");
            log_file.open(log_path, std::ios::out | std::ios::trunc);
            if (!log_file.is_open()) {
                logger::get()->fatal({"error opening process log file for [", log_path, "]"});
            }

            log_file << output;
            log_file.close();
        }

        /* update logfile every 1/10 second */
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::string process_logger::get_name() {
    if (!_name.empty()) {
        return _name;
    }
    std::string process_name = _sybling_ptr->get_name();
    if (process_name.empty()) {
        process_name = _sybling_ptr->get_running_command();

        /*
         * initialize process_name to the first unbroken word
         * will end up as something like "/bin/bash" or "bash"
         */
        process_name = process_name.substr(0, process_name.find(' '));
    }
    _name = process_name;
    return _name;
}


std::string process_logger::get_path() {
    if (!_path.empty()) {
        return _path;
    }
    if (_name.empty()) {
        get_name();
    }
    std::string home_dir = getenv("HOME");
    home_dir += "/.sybil/";
    std::string log_path = home_dir + _name + ".log";
    _path = log_path;
    return _path;
}

std::string process_logger::get_sybling_name() {
    return _sybling_ptr->get_name();
}

/* start logger on a separate thread */
bool process_logger::start_logger(process_logger* pl) {
    pl->_quit_logging = false;
    if (!pl->_sybling_ptr->is_reading()) {
        return false;
    }
    std::thread logger_thread(&process_logger::_writer, pl);
    logger_thread.detach();
    return true;
}

void process_logger::stop_logger() {
    _quit_logging = true;
}