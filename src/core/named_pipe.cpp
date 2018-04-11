#include <core/named_pipe.h>
#include <core/logger.h>
#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <unistd.h>

using namespace sybil;

named_pipe::named_pipe(std::string file_path) {
    _path = file_path;
    mkfifo(_pipe, 0666);
}

void named_pipe::write(std::string text) {
    std::ofstream pipe_writer(_path);
    if (pipe_writer.is_open()) {
        pipe_writer << text;
        logger::get()->verbose({"wrote [", text, "] to [", _path, "]"});
        pipe_writer.close();
    }
}

void named_pipe::write(std::vector<std::string> text) {
    std::string buffer;
    for (auto iterator : text) {
        buffer += iterator;
    }
    write(buffer);
}

void named_pipe::clear_file() {
    std::ofstream pipe_clearer(_path, std::ios::trunc);
    if (pipe_clearer.is_open()) {
        pipe_clearer << "";
        pipe_clearer.close();
    }
}

std::string named_pipe::read() {
    std::ifstream pipe_reader(_path);

    /*
     * check if the pipe file actually exists
     * if it doesn't, create it and log errno
     */
    if (!pipe_reader.good()) {
        pipe_reader.close();
        logger::get()->debug("pipe nonexistent, creating...");
        int status = open(_path.c_str(), O_CREAT | O_RDWR, 0666);
        logger::get()->debug({"open status: [", std::to_string(status), "]"});
        logger::get()->debug({"errno: [", std::to_string(errno), "]"});
        close(status);
    }

    std::string line;
    logger::get()->verbose("starting read from named pipe");
    while (line.empty()) {
        pipe_reader.open(_path);
        std::getline(pipe_reader, line);
        pipe_reader.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    clear_file();
    logger::get()->verbose("finished read from named pipe");
    pipe_reader.close();
    return line;
}