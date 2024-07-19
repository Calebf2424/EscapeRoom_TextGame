@echo off

:: Function to check if the script is running as administrator
openfiles >nul 2>&1
if %errorlevel% NEQ 0 (
    echo Requesting administrative privileges...
    goto UACPrompt
) else (
    goto Admin
)

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0""", "", "runas", 1 >> "%temp%\getadmin.vbs"
    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:Admin
    echo Running with administrative privileges

    :: Switch to the Program Files directory
    cd /d "C:\Program Files"

    :: Clone the repository
    git clone https://github.com/Calebf2424/EscapeRoom_TextGame.git

    pause
