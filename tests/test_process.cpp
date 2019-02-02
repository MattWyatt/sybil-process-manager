#include <gtest/gtest.h>
#include <core/process.h>

TEST(test_process, start) {
    sybil::process p([]() {
        return;
    });

    ASSERT_GT(p.get_pid(), 0);
    p.wait_for_exit();
}

TEST(test_process, output_realtime) {
    sybil::process p([]() {
        std::cout << "test";
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ASSERT_EQ(p.output(), "test");

    p.wait_for_exit();
}

TEST(test_process, output_post) {
    sybil::process p([]() {
        std::cout << "test";
    });

    p.wait_for_exit();

    ASSERT_EQ(p.output(), "test");
}


TEST(test_process, write_to) {
    sybil::process p([]() {
        std::string s;
        std::cin >> s;
        std::cout << s;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    p.write_to("test\n\r");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_EQ(p.output(), "test");

    p.wait_for_exit();
}