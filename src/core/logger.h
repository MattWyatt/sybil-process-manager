/*
 * sybil::logger
 *
 * Logger class responsible for writing messages to a logfile and outputting
 * them if necessary
 */

#ifndef SYBIL_PROCESS_MANAGER_LOGGER_H
#define SYBIL_PROCESS_MANAGER_LOGGER_H

#include <string>
#include <mutex>
#include <fstream>

namespace sybil {
    enum log_level {
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR,
        LOG_FATAL
    };

    class logger {
    private:
        std::ofstream _log_file;
        log_level _level;
        static std::mutex _log_mutex;

    public:
        logger();

        explicit logger(const std::string& file_path);

        logger(const std::string& file_path, const sybil::log_level& level);

        ~logger();


        void log(const sybil::log_level& level, const std::string& prefix, const std::string& text);

        void debug(const std::string& text);

        void info(const std::string& text);

        void warn(const std::string& text);

        void error(const std::string& text);

        void fatal(const std::string& text);

        void set_level(const log_level& level);

        const sybil::log_level& get_level() const;
    };

    /* global default logger */
    extern sybil::logger log;
}


#endif //SYBIL_PROCESS_MANAGER_LOGGER_H
