@echo off

REM Change directory to your FinanceApp directory
cd C:\Program Files\EscapeRoom_TextGame

REM Pull the latest changes from the main branch
git pull origin main

REM Remove the existing 'build' directory and all its contents
rmdir /s /q build

REM Create a new 'build' directory
mkdir build

REM Change directory to the 'build' directory
cd build

REM Run CMake to configure the build environment
cmake ..

REM Build the project using CMake
cmake --build .

REM Execute the compiled executable
.\Debug\EscapeRoom_TextGame.exe

REM Pause to keep the Command Prompt window open after execution (optional)
pause
