cmake_minimum_required(VERSION 3.1)
project(game C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Manually include and link Raylib
include_directories("/home/killswitch/raylib/src")
link_directories("/home/killswitch/raylib/build/raylib")

# Define source files
set(SOURCES
    ../main.c
    ../bullet.c
    ../player.c
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link to Raylib and dependencies
target_link_libraries(${PROJECT_NAME}
    raylib
    m
    pthread
    dl
    rt
    X11
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
