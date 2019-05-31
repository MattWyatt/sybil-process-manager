/*
 * sybil::process_pipe
 *
 * Simple class that represents a pipe between two processes
 * and easily separates the reading and writing ends
 */

#ifndef SYBIL_PROCESS_MANAGER_PIPE_H
#define SYBIL_PROCESS_MANAGER_PIPE_H

namespace sybil {

    const int PIPE_READ = 0;
    const int PIPE_WRITE = 1;

    class process_pipe {
    private:
        int _input_pipe[2];
        int _output_pipe[2];

    public:
        process_pipe();

        int iread();

        int iwrite();

        int oread();

        int owrite();
    };
}


#endif //SYBIL_PROCESS_MANAGER_PIPE_H
