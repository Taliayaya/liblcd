cmake_minimum_required(VERSION 3.21)
project(liblcd)

target_sources(liblcd PRIVATE
lcd_1inch69.cpp
lcd_1inch69.hpp
lcd_rgb565.cpp
lcd_rgb565.hpp
lcd_dsi.hpp
lcd_dsi.cpp
)
