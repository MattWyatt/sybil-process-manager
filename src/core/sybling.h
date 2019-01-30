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
        sybling(std::string& name, std::string& path);

        sybling(std::string& name, std::string& path, std::vector<std::string>& args);

        const std::string& get_name() const;

        const pid_t& get_pid() const;
    };
}


#endif //SYBIL_PROCESS_MANAGER_OVERSEER_H
