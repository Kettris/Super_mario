@echo off
setlocal

echo Building Super Mario...

set BUILD_TYPE="Ninja"
set BUILD_FOLDER=build_qt_game
set SOURCE_FOLDER=src

if exist %BUILD_FOLDER% (
    echo Removing old build directory...
    rmdir /s /q %BUILD_FOLDER%
)

mkdir %BUILD_FOLDER%
cd %BUILD_FOLDER%

echo Configuring CMake...
cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building...
cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

cd ..

if exist "%BUILD_FOLDER%\super_mario.exe" (
    echo.
    echo Build successful! Running super_mario.exe...
    start "" "%BUILD_FOLDER%\super_mario.exe"
) else (
    echo.
    echo Error: Executable not found!
)

pause