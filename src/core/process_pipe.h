#ifndef SYBIL_PROCESS_MANAGER_PIPE_H
#define SYBIL_PROCESS_MANAGER_PIPE_H

const int PIPE_READ = 0;
const int PIPE_WRITE = 1;

namespace sybil {
    class process_pipe {
    private:
        int* _stdinput;
        int* _stdoutput;

    public:
        process_pipe();
        int* get_stdin();
        int* get_stdout();
    };
}


#endif //SYBIL_PROCESS_MANAGER_PIPE_H
