/*
 * class to parse and check validity of commands
 */

#ifndef SYBIL_PROCESS_MANAGER_COMMAND_PARSER_H
#define SYBIL_PROCESS_MANAGER_COMMAND_PARSER_H

#include <vector>
#include <string>

namespace sybil {
    class command_parser {
    private:

        /*
         * list of error messages to be printed
         * ordered in the same order as ERROR_CODES
         */
        static std::vector<std::string> _error_messages;

        /*
         * list of error codes to be returned by parse
         * these can be matched with their corresponding error message
         */
        enum _error_codes  {
            COMMAND_GOOD=1,
            INVALID_COMMAND,
            INVALID_ARGUMENT
        };

    public:
        static std::string extract_command(std::string full_command);
        static std::vector<std::string> split_command(std::string full_command);
        static std::string get_error_message(int error_code);
        static int parse(std::string command);
    };
}


#endif //SYBIL_PROCESS_MANAGER_COMMAND_PARSER_H
