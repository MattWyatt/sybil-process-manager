cmake_minimum_required(VERSION 3.9)
project(sybil-process-manager C CXX)

# set this variable to TRUE or FALSE in order to control building tests
# note that building tests does in-fact compile the object files a second time as of now
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(tests)