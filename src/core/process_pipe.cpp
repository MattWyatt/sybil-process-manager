#include <core/process_pipe.h>
#include <core/logger.h>
#include <unistd.h>

using namespace sybil;

process_pipe::process_pipe() {
    _stdinput = new int[2];
    _stdoutput = new int[2];
    if (pipe(_stdinput) < 0) {
        logger::get()->fatal("failed to create standard input process_pipe!");
        return;
    }
    if (pipe(_stdoutput) < 0) {
        close(_stdinput[PIPE_READ]);
        close(_stdinput[PIPE_WRITE]);
        logger::get()->fatal("failed to create standard output pipe!");
        return;
    }
}

int* process_pipe::get_stdin() {
    return _stdinput;
}

int* process_pipe::get_stdout() {
    return _stdoutput;
}