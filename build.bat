@echo off
REM Build script for WinAPI UDP Screen Capture - Obvious Edition
REM This batch file compiles the obvious capture and receiver executables
REM Any build monitoring will see this sh*t happening

echo ===================================================
echo Building WinAPI UDP Screen Capture - Obvious Edition
echo WARNING: This creates obvious executable files
echo ===================================================

REM Check if Visual Studio tools are available
where cl >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Visual Studio compiler not found in PATH
    echo You need to run this from a Visual Studio Developer Command Prompt
    echo Or install Visual Studio Build Tools, you dumb***
    pause
    exit /b 1
)

REM Create output directory for the compiled bullsh*t
if not exist "bin" mkdir bin

echo.
echo [COMPILING] Building capture.exe - obvious screen capture tool
echo This will create an executable that screams "I'M CAPTURING SCREENS!"

REM Compile capture.cpp with all the obvious libraries
cl /EHsc /O2 /Fe:bin\capture.exe capture.cpp ws2_32.lib gdi32.lib user32.lib

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile capture.cpp - this sh*t is broken
    pause
    exit /b 1
)

echo [SUCCESS] capture.exe compiled - ready to be detected by anti-cheat

echo.
echo [COMPILING] Building receiver.exe - obvious network server
echo This will create a UDP server that's obvious as f***

REM Compile receiver.cpp with networking libraries
cl /EHsc /O2 /Fe:bin\receiver.exe receiver.cpp ws2_32.lib

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile receiver.cpp - networking bullsh*t failed
    pause
    exit /b 1
)

echo [SUCCESS] receiver.exe compiled - ready to trigger network monitoring

REM Clean up object files because we're not complete animals
if exist "capture.obj" del capture.obj
if exist "receiver.obj" del receiver.obj

echo.
echo ===================================================
echo BUILD COMPLETE - Both executables are ready
echo ===================================================
echo.
echo Files created in bin\ directory:
echo - capture.exe   : Screen capture tool (obvious as hell)
echo - receiver.exe  : UDP receiver (network server bullsh*t)
echo.
echo USAGE:
echo 1. Run receiver.exe first (starts UDP server)
echo 2. Run capture.exe to start capturing screens
echo 3. Watch your anti-cheat detection systems go crazy
echo.
echo REMINDER: This is designed to be detected!
echo Don't use this obvious sh*t for actual cheating.
echo ===================================================

pause