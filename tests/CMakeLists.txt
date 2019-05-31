project(sybil-process-manager)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/include)

set(TEST_SRCS
        test_process.cpp
        test_sybling.cpp
        test_logger.cpp
        test_locker.cpp test_named_pipe.cpp)

add_executable(sybil_test main.cpp ${TEST_SRCS})
enable_testing()
add_test(tests sybil_test)

target_link_libraries(sybil_test
        core
        cli
        pthread
        gtest)