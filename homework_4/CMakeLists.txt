cmake_minimum_required(VERSION 3.5)
project(homework_4)
add_executable(homework_4 threadpool.cpp main.cpp)
target_link_libraries(homework_4 PRIVATE pthread)
