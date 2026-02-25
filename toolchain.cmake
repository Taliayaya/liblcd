set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# The sysroot folder should contain all the library necessary to compile.
# It should be a mirror of a raspberry pi architecture.
# ${CMAKE_SYSROOT}/lib -> usr/lib/
# ${CMAKE_SYSROOT}/opt
# ${CMAKE_SYSROOT}/usr
# ${CMAKE_SYSROOT}/usr/include
# ${CMAKE_SYSROOT}/usr/lib
# ${CMAKE_SYSROOT}/usr/local
#
set(CMAKE_SYSROOT /app/sysroot)


# These envs variable were added for libs that were not find correctly
# Add yours if needed
# set(Python3_NumPy_INCLUDE_DIR "${CMAKE_SYSROOT}/usr/include/numpy")
# set(OPENSSL_ROOT_DIR          "${CMAKE_SYSROOT}/usr/local")
# set(OPENSSL_SSL_LIBRARY       "${CMAKE_SYSROOT}/usr/local/lib/libssl.so.3")
# set(OPENSSL_CRYPTO_LIBRARY    "${CMAKE_SYSROOT}/usr/local/lib/libcrypto.so.3")
# 
# set(OPENSSL_INCLUDE_DIR "${CMAKE_SYSROOT}/usr/local/include")

set(ARM_LIB_DIRS
    "${CMAKE_SYSROOT}/usr/local/lib"
    "${CMAKE_SYSROOT}/opt/ros/jazzy/lib"
    "${CMAKE_SYSROOT}/usr/local/lib/pulseaudio"
)

set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

set(ENV{PKG_CONFIG_SYSROOT_DIR} "${CMAKE_SYSROOT}")
set(ENV{PKG_CONFIG_PATH} "/app/sysroot/usr/local/lib/aarch64-linux-gnu/pkgconfig:/app/sysroot/usr/local/lib/pkgconfig:/app/sysroot/usr/lib/aarch64-linux-gnu/pkgconfig")

# mold should drastically increase the linking speed
# it is a bit more strict (especially with .a libs)  so if linking fails,
# just comment the lines below
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold")
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=mold")

# We need to thell the compiler where to find the libs in the sysroot,
# most were installed in SYSROOT/usr/local/lib which isn't the most natural path
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SYSROOT}/usr/local"
                              "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu"
                              "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/cmake/opencv4")
list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SYSROOT}/usr/local/lib"
                                "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu"
)
set(CMAKE_FIND_ROOT_PATH ${COLCON_INSTALL_DIR}
                         ${CMAKE_SYSROOT}
                         ${CMAKE_SYSROOT}/usr/local
                         ${CMAKE_SYSROOT}/opt/ros/jazzy)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


# the follow line ensure the libs are correctly found, feel free to modify the
# ARM_LIB_DIRS variable above
foreach(dir ${ARM_LIB_DIRS})
    set(LINKER_EXTRA_FLAGS "${LINKER_EXTRA_FLAGS} -L${dir} -Wl,-rpath-link,${dir}")
endforeach()

set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_EXTRA_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_EXTRA_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_EXTRA_FLAGS}")
