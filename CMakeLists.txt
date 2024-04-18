cmake_minimum_required(VERSION 2.8)
project(lablib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_ALL_INC})

add_library(lablib lib/lablib.c lib/button.c lib/scene.c lib/input.c lib/cursor.c)
target_link_libraries(lablib ${SDL2_ALL_LIBS})

add_executable(main main.c)
target_link_libraries(main ${SDL2_ALL_LIBS} SDL2_TTF  SDL2_image lablib)
