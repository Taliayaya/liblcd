BUILD_DIR=build
TOOLCHAIN=toolchain.cmake

cmake -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"
cmake --install "$BUILD_DIR"