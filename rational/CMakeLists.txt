cmake_minimum_required(VERSION 3.24)
project(rational)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_subdirectory(rational)

add_executable(main main.cpp)

target_link_libraries(main rational)
