cmake_minimum_required(VERSION 3.20)
project(IZ-2)

add_compile_options(-Wall -Werror -Wpedantic)

add_executable(IZ-2 main.c)

add_subdirectory(lib_static)
target_link_libraries(IZ-2 lib_static)
