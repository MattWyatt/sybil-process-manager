#ifndef SYBIL_PROCESS_MANAGER_NAMED_PIPE_H
#define SYBIL_PROCESS_MANAGER_NAMED_PIPE_H

#include <string>
#include <vector>

namespace sybil {
    /*
     * class to represent a named pipe
     * handles creating, writing, and reading on a pipe
     * also abstracts everything through strings
     */
    class named_pipe {
    private:
        std::string _path;
        char* _pipe;
        std::string _buffer;
    public:
        named_pipe(std::string file_path);
        void write(std::string text);
        void write(std::vector<std::string> text);
        void clear_file();
        std::string read();
    };
}


#endif //SYBIL_PROCESS_MANAGER_NAMED_PIPE_H
