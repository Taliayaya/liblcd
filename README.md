# liblcd

A lib to interface LCD screen for raspberry PI
It uses OpenCV to quickly convert the formats to the ones used by the screens

Dependencies include:
- libgpio-dev (-llgpio)
- math (-lm)
- OpenCV

Supported screens:
- LCD_1INCH69_240x280
- LCD_DSI,

- 

Outputs the `liblcd.so` library.

Public API is available from `include/lcd/lcd.hpp`. It is the same for all
screens.

## Building

Go to root directory

```sh
cd liblcd/
```

Initialize cmake

```
cmake -S . -B build
```

Build files
```
cmake --build build -j
```

## Install


Root permissions may be necessary
```
cmake --install build
```


## Import in other projects with CMake

This project installs the .so and include folders as well as creates
a liblcd.pc file that can be used to easily manipulate the project with cmake.

```cmake
find_package(PkgConfig REQUIRED)

pkg_check_modules(liblcd REQUIRED liblcd)

target_link_libraries(EXE_NAME
    ${liblcd_LIBRARIES}
)
target_include_directories(EXE_NAME
    ${liblcd_INCLUDE_DIRS}
)

```

## Example usage

```cpp
#include <lcd/lcd.hpp>

int main()
{
    // Crée une nouvelle instance de notre écran
    auto lcd = lcd::make_lcd(lcd::LCD_1INCH69_240x280);

    // Charge l’image dans le buffer
    lcd−>loadFromFile(”image.png”) ;

    // Met a jour l’affichage sur l’ecran
    lcd−>refresh();

    return 0;
}

```
