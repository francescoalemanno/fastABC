
cmake_minimum_required(VERSION 3.16)
add_compile_options(-O3 --std=c++17)
project(application)

add_executable(application application.cpp)

install(TARGETS application)

enable_testing()
add_test(NAME application COMMAND application)