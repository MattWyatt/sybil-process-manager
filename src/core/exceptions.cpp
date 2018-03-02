#include "exceptions.h"
#include "logger.h"

const char* sybil::process_start_error::what() {
    logger::get()->write("failed to spawn child", logger::DEBUG);
    return "failed to spawn child";
}

const char* sybil::process_execution_error::what() {
    logger::get()->write("failed to replace running process", logger::DEBUG);
    return "failed to replace running process";
}

const char* sybil::process_termination_error::what() {
    logger::get()->write("failed to terminate process correctly", logger::DEBUG);
    return "failed to terminate process correctly";
}