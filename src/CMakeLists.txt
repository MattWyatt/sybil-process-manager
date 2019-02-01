project(sybil-process-manager)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(core)
add_subdirectory(cli)


add_executable(sybil main.cpp)

# link source libraries
target_link_libraries(sybil
        core
        cli
        pthread)