#include <core/logger.h>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

sybil::logger sybil::log;

std::mutex sybil::logger::_log_mutex;

sybil::logger::logger() : _level(sybil::log_level::LOG_INFO) {
    std::string file_path = getenv("HOME");
    file_path.append("/.sybil/sybil.log");
    _log_file = std::ofstream(file_path);
}

sybil::logger::logger(const std::string& file_path) : _level(sybil::log_level::LOG_INFO) {
    _log_file = std::ofstream(file_path);
}

sybil::logger::logger(const std::string& file_path, const sybil::log_level& level) : _level(level) {
    _log_file = std::ofstream(file_path);
}

sybil::logger::~logger() {
    _log_file.close();
}


void sybil::logger::log(const sybil::log_level &level, const std::string &prefix, const std::string& text) {
    /* get the system time for logging
     * we have to convert it to a time_t to actually print it*/
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    /* create a stream to write output to
     * we do all formatting right here*/
    std::stringstream output;
    output << "["
           << prefix
           << " "
           << std::put_time(std::localtime(&now_c), "%F %T")
           << "] "
           << text << std::endl;

    /* convert the stream to a string for easy printing */
    std::string str_output = output.str();

    /* acquire a lock guard on the logger mutex
     * so that no two loggers can write at the same time to the same file */
    std::lock_guard<std::mutex> lock(_log_mutex);

    /* actually write to the streams
     * because all the formatting took place earlier
     * we can add more stuff to write to here if required */
    _log_file << str_output;
    if (level >= _level) {
        std::cout << str_output;
    }
    _log_file.flush();
}

void sybil::logger::debug(const std::string& text) {
    log(LOG_DEBUG, "DEBUG", text);
}

void sybil::logger::info(const std::string& text) {
    log(LOG_INFO, "INFO", text);
}

void sybil::logger::warn(const std::string &text) {
    log(LOG_WARN, "WARN", text);
}

void sybil::logger::error(const std::string &text) {
    log(LOG_ERROR, "ERROR", text);
}

void sybil::logger::fatal(const std::string &text) {
    log(LOG_FATAL, "FATAL", text);
}

void sybil::logger::set_level(const sybil::log_level &level) {
    _level = level;
}

const sybil::log_level& sybil::logger::get_level() const {
    return _level;
}