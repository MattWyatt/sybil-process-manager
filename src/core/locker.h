#ifndef SYBIL_PROCESS_MANAGER_LOCKER_H
#define SYBIL_PROCESS_MANAGER_LOCKER_H

#include <string>

namespace sybil {

    /*
     * class to create and represent a lock on a file
     * used by the daemon process to keep a singleton instance of the actual process
     */
    class locker {
    private:
        std::string _path;
        int _file;
        int _lock;
        bool _locked = false;
        int _lock_error;

    public:
        locker(std::string lock_file);
        bool is_locked();
        int get_lock_error();
    };
}


#endif //SYBIL_PROCESS_MANAGER_LOCKER_H
