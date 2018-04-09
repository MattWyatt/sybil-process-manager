project(sybil-process-manager)
include_directories(./)

# source files are included in this SET statement
set(SRCS process.cpp
        exceptions.cpp
        logger.cpp
        sybling.cpp
        process_pipe.cpp
        daemon.cpp
        locker.cpp
        named_pipe.cpp
        process_logger.cpp)