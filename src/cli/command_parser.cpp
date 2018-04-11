#include <cli/command_parser.h>
#include <sstream>
#include <iterator>

using namespace sybil;

std::vector<std::string> command_parser::_error_messages = {
    "COMMAND GOOD",
    "NO ARGUMENT ZERO",
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

int command_parser::parse(std::string command)  {

    /*
     * check for validity of argv[0]
     * if this fails we've a serious problem
     * this could be a redundant statement
     */
    if (command.substr(0, command.find(' ')) != "sybil") {
        return _error_codes::NO_ARGV_0;
    }

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
            split_command.at(0) != "status") {
        return _error_codes::INVALID_COMMAND;
    }
}