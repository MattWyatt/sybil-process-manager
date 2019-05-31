#include <fstream>
#include <thread>

#include <gtest/gtest.h>

#include "core/named_pipe.h"

TEST(test_named_pipe, create) {
    sybil::named_pipe np("file.pipe");

    std::ofstream o("file.pipe");

    ASSERT_TRUE(o.good());

    o.close();

    remove("file.pipe");
}

TEST(test_named_pipe, send_receive) {
    pid_t pid = fork();

    if (pid == 0) {
        sybil::named_pipe np("file.pipe");
        np.send("test");
        exit(0);
    }
    else {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sybil::named_pipe np("file.pipe");
        std::string message = np.receive();
        ASSERT_EQ(message, "test");
    }

    remove("file.pipe");
}