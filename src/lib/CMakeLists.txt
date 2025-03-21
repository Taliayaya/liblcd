cmake_minimum_required(VERSION 3.21)
project(liblcd)

target_sources(liblcd PRIVATE
LCD_1in69.c
LCD_1in69.h
)

add_subdirectory(config)
add_subdirectory(fonts)
add_subdirectory(gui)