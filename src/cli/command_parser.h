/*
 * class to parse and check validity of commands
 */

#ifndef SYBIL_PROCESS_MANAGER_COMMAND_PARSER_H
#define SYBIL_PROCESS_MANAGER_COMMAND_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <iterator>

namespace sybil {
    class command_parser {
    private:

        /*
         * list of error messages to be printed
         * ordered in the same order as ERROR_CODES
         */
        static std::vector<std::string> _error_messages = {
                "NO ARGUMENT ZERO",
                "INVALID COMMAND",
                "INVALID ARGUMENT PASSED"
        };

        /*
         * list of error codes to be returned by parse
         * these can be matched with their corresponding error message
         */
        static enum _error_codes {
            NO_ARGV_0,
            INVALID_COMMAND,
            INVALID_ARGUMENT
        };

    public:

        static int parse(std::string command) {

            /*
             * check for validity of argv[0]
             * if this fails we've a serious problem
             * this could be a redundant statement
             */
            if (command.substr(0, command.find(' ')) != "sybil") {
                return false;
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


        }
    };
}


#endif //SYBIL_PROCESS_MANAGER_COMMAND_PARSER_H
