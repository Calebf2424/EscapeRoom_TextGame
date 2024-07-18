@echo off
setlocal

:: Prompt user for file path
set /p filepath="Enter the path to your project directory: "

:: Check if the path exists
if not exist "%filepath%" (
    echo The specified path does not exist.
    pause
    exit /b 1
)

:: Change to the specified directory
cd "%filepath%" || (
    echo Failed to change to the specified directory.
    pause
    exit /b 1
)

:: Remove the build directory if it exists
rmdir /s /q build

:: Pull the latest changes from the main branch
git pull origin main

:: Create and navigate to the build directory
mkdir build
cd build

:: Run CMake commands
cmake .
cmake --build .

pause

