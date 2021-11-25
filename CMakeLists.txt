cmake_minimum_required(VERSION 3.5)
project(tetris)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window)

add_executable(tetris "src/main.cpp" "include/header.h" "include/tetromino.h" "src/tetromino.cpp")
target_include_directories(tetris PRIVATE src/include)
target_link_libraries(tetris PRIVATE sfml-graphics sfml-window)
install(TARGETS tetris)