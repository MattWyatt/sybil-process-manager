/*
 * sybil::sybling
 *
 * A sybling wraps a process and stores information about its
 * name, execution path, and IO
 */

#ifndef SYBIL_PROCESS_MANAGER_OVERSEER_H
#define SYBIL_PROCESS_MANAGER_OVERSEER_H

#include <core/process.h>

namespace sybil {
    class sybling  {
    private:
        std::unique_ptr<sybil::process> _process;

        std::string _name;

        std::string _path;

    public:
        sybling(const std::string& name, const std::string& path);

        sybling(const std::string& name, const std::string& path, std::vector<std::string>& args);

        const std::string& get_name() const;

        const pid_t& get_pid() const;

        const std::string output() const;

        void write_to(const std::string& input);

        void wait_for_exit();

        const bool running();

        void stop();
    };
}


#endif //SYBIL_PROCESS_MANAGER_OVERSEER_H
