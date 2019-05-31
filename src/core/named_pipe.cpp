#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include "named_pipe.h"


sybil::named_pipe::named_pipe(std::string path) : _path(std::move(path)),
                                                  _buffer_size(256) {}

sybil::named_pipe::named_pipe(std::string path, uint buffer_size) : _path(std::move(path)),
                                                                    _buffer_size(buffer_size) {}

void sybil::named_pipe::send(const std::string& message) {
    /* create a named pipe on the given filepath */
    mkfifo(_path.c_str(), 0666);

    /* open the file for writing only (O_WRONLY) */
    int fd = open(_path.c_str(), O_WRONLY);

    /* write the message to the file, using c_str() to convert */
    write(fd, message.c_str(), sizeof(message.c_str()));
    close(fd);
}

std::string sybil::named_pipe::receive() {
    char buffer[_buffer_size];

    /* open the file for reading only (O_RDONLY) */
    int fd = open(_path.c_str(), O_RDONLY);

    read(fd, buffer, _buffer_size);
    close(fd);

    return std::string(buffer);
}