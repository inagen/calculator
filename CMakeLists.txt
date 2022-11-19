cmake_minimum_required(VERSION 3.14)
project(calculator)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)


add_executable(calculator
                main.cpp
                token.cpp)