cmake_minimum_required(VERSION 3.25)
project(prj.cw)

set(CMAKE_CXX_STANDARD 17)

add_library(gradient_lib library.h library.cpp)
target_include_directories(gradient_lib PUBLIC ".")

find_package(OpenCV REQUIRED)
target_link_libraries(gradient_lib ${OpenCV_LIBS})

install(TARGETS gradient_lib)
install(TARGETS gradient_lib
        RUNTIME_DEPENDENCIES
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        DESTINATION bin
        )
