# PDF Editor C++ — Build Instructions

## Requirements

1. **Qt 6.4+**  
   Download: https://www.qt.io/download-qt-installer  
   Select: Qt 6.x → MSVC 2022 64-bit (or MinGW 64-bit)

2. **MuPDF**  
   Option A (recommended): vcpkg  
   ```
   git clone https://github.com/microsoft/vcpkg
   .\vcpkg\bootstrap-vcpkg.bat
   .\vcpkg\vcpkg install mupdf:x64-windows
   ```
   Option B: build from source  
   https://mupdf.com/releases/

3. **CMake 3.21+**  
   https://cmake.org/download/

4. **Visual Studio 2022** (Community edition is sufficient)  
   With workload: "Desktop development with C++"

---

## Build Steps

### With vcpkg (easiest method)

```bat
cd "PDF Editor\cpp"

cmake -B build -S . ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows ^
  -DCMAKE_PREFIX_PATH=C:/Qt/6.7.0/msvc2022_64 ^
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release -j 4
```

### With manually installed MuPDF

```bat
cmake -B build -S . ^
  -DMUPDF_DIR=C:/mupdf ^
  -DCMAKE_PREFIX_PATH=C:/Qt/6.7.0/msvc2022_64 ^
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release -j 4
```

The built executable is at: `build\Release\PDFEditor.exe`

---

## Deploying Qt DLLs (for distribution)

```bat
cd build\Release
C:\Qt\6.7.0\msvc2022_64\bin\windeployqt.exe PDFEditor.exe
```

---

## Keyboard Shortcuts (defaults)

| Action | Shortcut |
|---|---|
| Open | Ctrl+O |
| Save | Ctrl+S |
| Undo | Ctrl+Z |
| Redo | Ctrl+Y |
| Zoom in | Ctrl++ |
| Zoom out | Ctrl+- |
| Rotate left | Ctrl+[ |
| Rotate right | Ctrl+] |
| Fit to window | Ctrl+0 |
| Toggle sidebar | Ctrl+B |

All shortcuts can be changed under **Settings → Keyboard Shortcuts**.
