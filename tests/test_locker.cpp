#include <fstream>

#include <sys/file.h>

#include <gtest/gtest.h>

#include "core/locker.h"
#include "core/logger.h"


TEST(test_locker, create) {
    sybil::locker l("test_lock");
    std::ofstream o("test_lock");
    ASSERT_TRUE(o.good());
    o.close();
}

TEST(test_locker, not_locked) {
    sybil::locker l("test_lock");
    ASSERT_FALSE(l.was_already_locked());
}

TEST(test_locker, was_locked) {
    sybil::locker l("test_lock");
    ASSERT_FALSE(l.was_already_locked());

    sybil::locker l2("test_lock");
    ASSERT_TRUE(l2.was_already_locked());
}
