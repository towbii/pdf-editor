@echo off
setlocal

set QT_DIR=C:\Qt\6.11.1\msvc2022_64
set VCPKG_ROOT=C:\vcpkg
set VCPKG_TRIPLET=x64-windows

echo [1/3] Configuring...

if exist build rmdir /s /q build

cmake -B build -S . ^
  -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_PREFIX_PATH="%QT_DIR%" ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" ^
  -DVCPKG_TARGET_TRIPLET=%VCPKG_TRIPLET%

if errorlevel 1 (
    echo CMake failed!
    pause & exit /b 1
)

echo [2/3] Building...
cmake --build build --config Release -j 4
if errorlevel 1 (
    echo Build failed!
    pause & exit /b 1
)

echo [3/3] Deploying Qt DLLs...
"%QT_DIR%\bin\windeployqt.exe" build\Release\PDFEditor.exe

echo.
echo Done! Run: build\Release\PDFEditor.exe
pause
