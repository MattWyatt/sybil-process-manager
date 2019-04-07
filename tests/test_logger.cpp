#include <gtest/gtest.h>
#include <core/logger.h>

TEST(test_logger, create) {
    sybil::logger l;
    ASSERT_EQ(sybil::LOG_INFO, l.get_level());
}

TEST(test_logger, set_level) {
    sybil::logger l;
    ASSERT_EQ(sybil::LOG_INFO, l.get_level());

    l.set_level(sybil::LOG_DEBUG);
    ASSERT_EQ(sybil::LOG_DEBUG, l.get_level());
}

TEST(test_logger, writelog) {
    sybil::logger l("test.log");
    l.info("test");

    std::ifstream logfile("test.log");
    std::string test_output;

    for (int i = 0; i < 4; i++) {
        logfile >> test_output;
    }

    ASSERT_EQ("test", test_output);
}