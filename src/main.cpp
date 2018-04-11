#include <cli/command_parser.h>
#include <core/logger.h>
#include <core/daemon.h>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    sybil::logger::get()->set_level(sybil::logger::STANDARD);
    sybil::daemon d;

    std::vector<std::string> full_command;
    std::string final;
    for (int i = 0; i < argc; i++) {
        full_command.emplace_back(argv[i]);
    }
    for (auto iterator : full_command) {
        final += iterator;
        final += " ";
    }
    int code = sybil::command_parser::parse(final);
    if (code > 0) {
        std::cout << "error in command:" << std::endl << sybil::command_parser::get_error_message(code) << std::endl;
        return 0;
    }
    else {
        final = "sybil ";
        full_command.erase(full_command.begin(), full_command.begin()+1);
        for (auto iterator : full_command) {
            final += iterator;
            final += " ";
        }
        std::ofstream pipe_writer("/tmp/sybil.pipe");
        if (pipe_writer.is_open()) {
            pipe_writer << final;
            pipe_writer.close();
        }
        std::cout << final << std::endl;
        return 0;
    }
}