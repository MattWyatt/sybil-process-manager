#include <core/sybling.h>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>

/* these two constructors are particularly ugly
 * please refactor these later */
sybil::sybling::sybling(const std::string &name, const std::string &path) :
    /* initialize _process inline */
    _process(sybil::process([path]() {
        /* create the args array from the path and null */
        char* args[] = {(char*)path.c_str(), nullptr};

        /* execute from the args array */
        execvp(args[0], args);
    })), _name(name), _path(path) {}

sybil::sybling::sybling(const std::string& name, const std::string& path, std::vector<std::string>& args) :
    _process(sybil::process([path, args]() {

        /* create a vector and push back the path as the first element
         * this will let us call argv.data() for the execvp() */
        std::vector<char*> argv;
        argv.push_back((char*)path.c_str());

        /* copy everything from the args vector into the new one */
        for (auto& s : args) {
            argv.push_back((char*)s.c_str());
        }

        /* execute
         * the first element is going to be the path
         * argv.data() will emulate char* argv[] */
        execvp(argv[0], argv.data());
    })), _name(name), _path(path) {}

const std::string& sybil::sybling::get_name() const {
    return _name;
}

const pid_t& sybil::sybling::get_pid() const {
    return _process.get_pid();
}

const std::string sybil::sybling::output() const {
    return _process.output();
}

void sybil::sybling::write_to(const std::string& input) {
    _process.write_to(input);
}

void sybil::sybling::wait_for_exit() {
    _process.wait_for_exit();
}

const bool sybil::sybling::running() {
    /* call kill() with a signal of zero
     * if the call returns 0, the process is running */
    int status;
    if (waitpid(get_pid(), &status, WNOHANG) == 0) {
        return true;
    }

    return false;
}

void sybil::sybling::stop() {
    kill(get_pid(), SIGKILL);
}