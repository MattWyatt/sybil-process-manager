#include <core/process_pipe.h>
#include <core/logger.h>
#include <unistd.h>

sybil::process_pipe::process_pipe() {
    if (pipe(_input_pipe) < 0) {
        sybil::log.error("error creating input pipe");
        throw "error creating input pipe";
    }

    if (pipe(_output_pipe) < 0) {
        sybil::log.error("error creating output pipe");
        throw "error creating output pipe";
    }
}

int sybil::process_pipe::iread() {
    return _input_pipe[0];
}

int sybil::process_pipe::iwrite() {
    return _input_pipe[1];
}

int sybil::process_pipe::oread() {
    return _output_pipe[0];
}

int sybil::process_pipe::owrite() {
    return _output_pipe[1];
}