cmake_minimum_required(VERSION 3.10)
project(mathparser)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src bin/mathparser)
add_subdirectory(tst bin/tst)
add_subdirectory(tst/googletest)
