cmake_minimum_required(VERSION 3.27)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

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
        tree.c)
