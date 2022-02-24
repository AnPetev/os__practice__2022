cmake_minimum_required(VERSION 3.5)
project(homework_2)
add_executable(homework_2 main.cpp blocking_queue.cpp)
target_include_directories(homework_2 PRIVATE "./include")
