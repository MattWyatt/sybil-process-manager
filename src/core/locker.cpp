#include <fstream>

#include <sys/file.h>
#include <unistd.h>

#include <core/locker.h>
#include <core/logger.h>


sybil::locker::locker(const std::string& lock_file) : _path(lock_file) {
    /* open the lock file and create an exclusive lock on it */
    _file = open(_path.c_str(), O_RDWR | O_CREAT, 0666);
    _lock = flock(_file, LOCK_EX | LOCK_NB);
}

bool sybil::locker::was_already_locked() {
    if (_lock != 0) {
        return true;
    }
    return false;
}

sybil::locker::~locker() {
    flock(_file, LOCK_UN);
    close(_file);
    remove(_path.c_str());
}