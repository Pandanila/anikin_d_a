cmake_minimum_required(VERSION 3.24)
project(prj.cw)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(gradient_lib)

add_executable(test test.cpp)


target_link_libraries(test gradient_lib)


install (FILES
        "visualisation.py"
        DESTINATION bin)
install(TARGETS test)
install(TARGETS test
        RUNTIME_DEPENDENCIES
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        DESTINATION bin
        )

