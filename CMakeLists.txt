# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(EscapeRoom_TextGame CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(Include)

# Add executable target
add_executable(EscapeRoom_TextGame
    src/main.cpp
    src/Room.cpp
    src/Item.cpp
)

#set(CMAKE_BUILD_TYPE Release)
