/*
 * sybil::named_pipe
 *
 * class that represents a named pipe for interprocess communication
 *
 * the daemon will receive while the client(s) may send commands
 * to be executed by the daemon
 */

#ifndef SYBIL_PROCESS_MANAGER_NAMED_PIPE_H
#define SYBIL_PROCESS_MANAGER_NAMED_PIPE_H

#include <string>
#include <vector>

namespace sybil {
    class named_pipe {
    private:
        uint _buffer_size;
        std::string _path;

    public:
        named_pipe(std::string path);

        named_pipe(std::string path, uint buffer_size);

        void send(const std::string& message);

        std::string receive();
    };
}


#endif //SYBIL_PROCESS_MANAGER_NAMED_PIPE_H
