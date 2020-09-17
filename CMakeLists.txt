
cmake_minimum_required(VERSION 3.16)

project(application)

add_executable(application application.cpp)

install(TARGETS application)

enable_testing()
add_test(NAME application COMMAND application)