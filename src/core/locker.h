/*
 * sybil::locker
 *
 * class to create and represent a lock on a file
 * used by the daemon process to keep a singleton instance of the actual process
 */

#ifndef SYBIL_PROCESS_MANAGER_LOCKER_H
#define SYBIL_PROCESS_MANAGER_LOCKER_H

#include <string>

namespace sybil {
    class locker {
    private:
        std::string _path;
        size_t _file;
        int _lock;

    public:
        explicit locker(const std::string& lock_file);

        bool was_already_locked();

        ~locker();
    };
}


#endif //SYBIL_PROCESS_MANAGER_LOCKER_H
