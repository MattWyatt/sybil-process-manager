#include <core/locker.h>
#include <core/logger.h>
#include <sys/file.h>
#include <fstream>

using namespace sybil;

locker::locker(std::string lock_file) {
    _path = lock_file;
    /* open the lock file and create an exclusive lock on it */
    logger::get()->verbose({"attempting to create lock on [", _path, "]"});
    _file = open(_path.c_str(), O_RDWR | O_CREAT, 0666);
    logger::get()->verbose({"lockfile identifier is [", std::to_string(_file), "]"});
    _lock = flock(_file, LOCK_EX | LOCK_NB);
    logger::get()->debug({"flock() returned ", std::to_string(_lock)});

    /* check if the file is actually locked
     * if it is, then set _locked to true
     * if it isn't locked for whatever reason, then save the errno
     */
    if (_lock) {
        if (EWOULDBLOCK == errno) {
            logger::get()->verbose({"lock on [", _path, "] is active"});
            _locked = true;
        }
        else {
            logger::get()->debug({"error locking [", _path, "] error code: ", std::to_string(errno)});
            _locked = true;
            _lock_error = errno;
        }
    }
}

bool locker::is_locked() {
    return _locked;
}

int locker::get_lock_error() {
    return _lock_error;
}