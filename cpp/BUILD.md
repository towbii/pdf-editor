# PDF Editor C++ — Build Instructions

## Voraussetzungen

1. **Qt 6.4+**  
   Download: https://www.qt.io/download-qt-installer  
   Wähle: Qt 6.x → MSVC 2022 64-bit (oder MinGW 64-bit)

2. **MuPDF**  
   Option A (empfohlen): vcpkg  
   ```
   git clone https://github.com/microsoft/vcpkg
   .\vcpkg\bootstrap-vcpkg.bat
   .\vcpkg\vcpkg install mupdf:x64-windows
   ```
   Option B: Quellcode bauen  
   https://mupdf.com/releases/

3. **CMake 3.21+**  
   https://cmake.org/download/

4. **Visual Studio 2022** (Community reicht)  
   Mit Workload: "Desktop-Entwicklung mit C++"

---

## Build-Schritte

### Mit vcpkg (einfachste Methode)

```bat
cd "PDF Editor\cpp"

cmake -B build -S . ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows ^
  -DCMAKE_PREFIX_PATH=C:/Qt/6.7.0/msvc2022_64 ^
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release -j 4
```

### Mit manuell installiertem MuPDF

```bat
cmake -B build -S . ^
  -DMUPDF_DIR=C:/mupdf ^
  -DCMAKE_PREFIX_PATH=C:/Qt/6.7.0/msvc2022_64 ^
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release -j 4
```

Die fertige EXE liegt in: `build\Release\PDFEditor.exe`

---

## Qt DLLs deployen (für Weitergabe)

```bat
cd build\Release
C:\Qt\6.7.0\msvc2022_64\bin\windeployqt.exe PDFEditor.exe
```

---

## Shortcuts (Standard)

| Aktion | Kürzel |
|---|---|
| Öffnen | Ctrl+O |
| Speichern | Ctrl+S |
| Rückgängig | Ctrl+Z |
| Wiederholen | Ctrl+Y |
| Vergrößern | Ctrl++ |
| Verkleinern | Ctrl+- |
| Links drehen | Ctrl+[ |
| Rechts drehen | Ctrl+] |
| Zoom anpassen | Ctrl+0 |
| Seitenleiste | Ctrl+B |

Alle Shortcuts können unter **Einstellungen → Tastenkürzel** geändert werden.
