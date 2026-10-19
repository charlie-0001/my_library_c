cmake_minimum_required(VERSION 3.20)
project(my_library_c C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_library(my_library_c STATIC
        src/array_tools.c
)

add_executable(main_test
        tests/main.c
)

target_link_libraries(main_test PRIVATE my_library_c)