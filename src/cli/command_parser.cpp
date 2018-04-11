#include <cli/command_parser.h>
#include <sstream>
#include <iterator>

using namespace sybil;

std::vector<std::string> command_parser::_error_messages = {
    "COMMAND GOOD",
    "INVALID COMMAND",
    "INVALID ARGUMENT PASSED"
};

std::string command_parser::extract_command(std::string full_command) {
    return full_command.substr(full_command.find(' '));
}

std::vector<std::string> command_parser::split_command(std::string full_command) {
    std::vector<std::string> split_command;
    std::istringstream streamer(full_command);
    std::istream_iterator<std::string> command_iterator(streamer);
    std::istream_iterator<std::string> empty_iterator;
    auto word_splitter = std::back_inserter(split_command);
    std::copy(command_iterator, empty_iterator, word_splitter);
    return split_command;
}

std::string command_parser::get_error_message(int error_code) {
    return _error_messages.at(error_code-1);
}

int command_parser::parse(std::string command)  {
    /*
     * split the command into words and store them in a vector
     * this will allow for individual parsing of each command and it's arguments
     */
    std::string working_command;
    working_command = command.substr(command.find(' '));
    std::vector<std::string> split_command;
    std::istringstream streamer(working_command);
    std::istream_iterator<std::string> command_iterator(streamer);
    std::istream_iterator<std::string> empty_iterator;
    auto word_splitter = std::back_inserter(split_command);
    std::copy(command_iterator, empty_iterator, word_splitter);

    if (split_command.at(0) != "new" &&
            split_command.at(0) != "start" &&
            split_command.at(0) != "stop" &&
            split_command.at(0) != "send" &&
            split_command.at(0) != "status" &&
            split_command.at(0) != "quit") {
        return _error_codes::INVALID_COMMAND;
    }
    return 0;
}