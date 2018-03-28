project(sybil-process-manager)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(DIRS ../src/core)
foreach(dir ${DIRS})
    # grab all source files for each folder inside /src
    get_directory_property(DIR_SRCS DIRECTORY ${dir} DEFINITION SRCS)
    foreach (src ${DIR_SRCS})
        list(APPEND SOURCE "${dir}/${src}")
    endforeach(src)

    # include the cmakelists in the project
    list(APPEND SOURCE "${dir}/CMakeLists.txt")
endforeach(dir)

list(APPEND SOURCE "${SRCS}")
message(STATUS "SOURCES: ${SOURCE}")

# add future tests here and link threads to them

add_executable(file_test file_test.cpp ${SOURCE})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(file_test Threads::Threads)