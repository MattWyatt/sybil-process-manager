#include <gtest/gtest.h>
#include <core/sybling.h>

TEST(test_sybling, start) {
    sybil::sybling s("sybling", "/bin/ls");

    ASSERT_GT(s.get_pid(), 0);
    s.wait_for_exit();
}

TEST(test_sybling, output_realtime) {
    sybil::sybling s("sybling", "/bin/ls");

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ASSERT_FALSE(s.output().empty());
    s.wait_for_exit();
}

TEST(test_sybling, output_post) {
    sybil::sybling s("sybling", "/bin/ls");

    s.wait_for_exit();
    ASSERT_FALSE(s.output().empty());
}

TEST(test_sybling, write_to) {
    sybil::sybling s("sybling", "/bin/bash");

    s.write_to("echo -n test");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_EQ(s.output(), "test");

    s.write_to("exit");
    s.wait_for_exit();
}

TEST(test_sybling, running) {
    sybil::sybling s("sybling", "/bin/bash");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_TRUE(s.running());

    s.write_to("exit");
    s.wait_for_exit();
}

TEST(test_sybling, stop) {
    sybil::sybling s("sybling", "/bin/bash");

    ASSERT_TRUE(s.running());
    s.stop();
    s.wait_for_exit();
    ASSERT_FALSE(s.running());

}