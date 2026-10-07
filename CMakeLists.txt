cmake_minimum_required(VERSION 3.21)
project(liblcd)

include(GNUInstallDirs)  # This defines CMAKE_INSTALL_LIBDIR
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(liblcd SHARED)

find_library(LGPIO lgpio REQUIRED)
find_package(ament_cmake REQUIRED)

# GPIO/SPI backend used by src/lib/config/DEV_Config.c (lgpio)
target_compile_definitions(liblcd PRIVATE USE_DEV_LIB)

add_compile_options(-Wall -Wextra -Werror -pedantic)

# OPENCV ==
target_include_directories(liblcd PRIVATE ${OpenCV_INCLUDE_DIRS} 
                                          ${LGPIO_INCLUDE_DIR})
target_link_libraries( liblcd PUBLIC ${OpenCV_LIBS} PRIVATE ${LGPIO} m)

target_include_directories(liblcd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(liblcd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
target_include_directories(liblcd PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(liblcd PROPERTIES OUTPUT_NAME "lcd")

add_subdirectory(src)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/liblcd.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/liblcd.pc @ONLY
)

ament_export_targets(liblcd HAS_LIBRARY_TARGET)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/liblcd.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(TARGETS liblcd
    EXPORT liblcd
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

ament_export_dependencies(OpenCV)
ament_package()