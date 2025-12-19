@echo off
setlocal

echo Building Super Mario...

set BUILD_TYPE="Ninja"
set BUILD_FOLDER=build_ninja
set SOURCE_FOLDER=src

if exist %BUILD_FOLDER% (
    echo Removing old build directory...
    rmdir /s /q %BUILD_FOLDER%
)

mkdir %BUILD_FOLDER%
cd %BUILD_FOLDER%

echo Configuring CMake for main game...
cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building game...
cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

cd ..

echo.
echo Building Qt launcher...

set QT_BUILD_FOLDER=build_qt
set QT_SOURCE_FOLDER=src/qt

if exist %QT_BUILD_FOLDER% (
    rmdir /s /q %QT_BUILD_FOLDER%
)

mkdir %QT_BUILD_FOLDER%
cd %QT_BUILD_FOLDER%

echo Configuring CMake for Qt launcher...
cmake -G %BUILD_TYPE% ..\%QT_SOURCE_FOLDER%
if %ERRORLEVEL% NEQ 0 (
    echo Qt CMake configuration failed!
    pause
    exit /b 1
)

echo Building Qt launcher...
cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo Qt build failed!
    pause
    exit /b 1
)

cd ..

echo.
echo Build successful!
echo.

if exist "build_qt\super_mario_launcher.exe" (
    echo Running launcher...
    start "" "build_qt\super_mario_launcher.exe"
) else (
    echo Error: Launcher executable not found!
)

pause