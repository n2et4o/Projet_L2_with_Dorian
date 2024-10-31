cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL2-devel-2.30.5-mingw/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/SDL2_ttf-2.22.0/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(untitled1 main.c
        Code_fourni/loc.c
        Code_fourni/loc.h
        Code_fourni/moves.c
        Code_fourni/moves.h
        Code_fourni/map.c
        Code_fourni/map.h
        Code_fourni/queue.c
        Code_fourni/queue.h
        Code_fourni/stack.c
        Code_fourni/stack.h
        tree.h
        tree.c
        interfaces_graphiques.c)


target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} )