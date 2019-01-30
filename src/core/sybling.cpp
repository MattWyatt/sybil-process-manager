#include <core/sybling.h>
#include <unistd.h>

sybil::sybling::sybling(std::string &name, std::string &path) {
    _name = name;
    _path = path;

    /* look at this beautiful call
     * calls make_unique on a new instance of sybil::process
     * the underlying process object is now stored in _process under a smart pointer */
    _process = std::make_unique<sybil::process>(sybil::process([this]() {
        char* args[] = {(char*)_path.c_str(), nullptr};
        execvp(args[0], args);
    }));
}

sybil::sybling::sybling(std::string& name, std::string& path, std::vector<std::string>& args) {
    _name = name;
    _path = path;

    /* converting a vector of strings to a vector of char*
     * this is required so that argv.data() returns a char** */
    std::vector<char*> argv;
    for (auto& s : args) {
        argv.push_back((char*)s.c_str());
    }

    /* modern c++ looks really slick */
    _process = std::make_unique<sybil::process>(sybil::process([argv]() {
        execvp(argv[0], argv.data());
    }));
}

const std::string& sybil::sybling::get_name() const {
    return _name;
}

const pid_t& sybil::sybling::get_pid() const {
    return _process->get_pid();
}