@echo off
setlocal

:: Change to the specified directory
cd C:\Users\cfarn\EscapeRoom_TextGame

:: Remove the build directory if it exists
rmdir /s /q build

:: Pull the latest changes from the main branch
git pull origin main

:: Create and navigate to the build directory
mkdir build
cd build

:: Run CMake commands
cmake ..
cmake --build .

pause

