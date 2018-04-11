#include <cli/command_parser.h>
#include <core/logger.h>
#include <core/named_pipe.h>
#include <core/daemon.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>


int main(int argc, char* argv[]) {
    sybil::logger::get()->set_level(sybil::logger::STANDARD);
    sybil::daemon d;

    if (argc == 1) {
        std::cout << "no command supplied. quitting..." << std::endl;
        return 0;
    }

    sybil::named_pipe sybil_output("/tmp/sybil_console.pipe");

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

    else if (full_command.at(1) == "quit") {
        std::ofstream pipe_writer("/tmp/sybil.pipe");
        if (pipe_writer.is_open()) {
            pipe_writer << "quit";
            pipe_writer.close();
        }
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << sybil_output.read() << std::endl;
        return 0;
    }
}