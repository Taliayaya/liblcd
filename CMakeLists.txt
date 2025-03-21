cmake_minimum_required(VERSION 3.21)
project(lcd)

#find_library(lgpio lgpio REQUIRED)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(USE_DEV_LIB 1)
set(USELIB "USE_DEV_LIB")  # Example setting, you can change this dynamically

# Set the DEBUG flags
set(DEBUG "-D${USELIB}")

add_library(liblcd SHARED)

# Determine the library to link based on USELIB
if(USELIB STREQUAL "USE_BCM2835_LIB")
    set(LIBRARIES -lbcm2835 -lm)
elseif(USELIB STREQUAL "USE_WIRINGPI_LIB")
    set(LIBRARIES -lwiringPi -lm)
elseif(USELIB STREQUAL "USE_DEV_LIB")
    set(LIBRARIES -llgpio -lm)
endif()

target_compile_definitions(liblcd PUBLIC -D${USELIB})

add_compile_options(-Wall -Wextra -Werror -pedantic ${DEBUG} ${LIBRARIES})
target_link_options(liblcd PRIVATE ${LIBRARIES})

# OPENCV ==
target_include_directories(liblcd PRIVATE ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( liblcd ${OpenCV_LIBS} )

#target_link_libraries(liblcd PRIVATE lgpio)
# print the link options
message(STATUS "Link options: ${LIBRARIES}")

target_include_directories(liblcd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(liblcd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(liblcd PROPERTIES OUTPUT_NAME "lcd")

add_subdirectory(src)