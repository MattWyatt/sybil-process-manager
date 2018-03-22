project(sybil-process-manager)
include_directories(./)

# append any additional directories to this SET line
set(DIRS core)

foreach(dir ${DIRS})
    # add every subdirectory inside /src to the project
    add_subdirectory(${dir})

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
add_executable(sybil ./main.cpp ${SOURCE})

# link pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(sybil Threads::Threads)