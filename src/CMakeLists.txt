cmake_minimum_required(VERSION 3.21)
project(liblcd)

target_sources(liblcd PRIVATE lcd.cpp)

add_subdirectory(lib)
add_subdirectory(screens)