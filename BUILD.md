# Build Instructions

## Windows (Visual Studio)

1. **Prerequisites:**
   - Visual Studio 2019 or later
   - OpenGL development libraries
   - GLUT (OpenGL Utility Toolkit)

2. **Setup:**
   - Open `3D solar System.slnx` in Visual Studio
   - Ensure you have GLUT installed (freeglut is recommended)

3. **Build:**
   - Select configuration (Debug or Release)
   - Build Solution (Ctrl+Shift+B)

4. **Run:**
   - Press F5 to run the application

## Linux/Mac (Command Line)

1. **Install Dependencies:**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install freeglut3-dev libgl1-mesa-dev

   # macOS with Homebrew
   brew install freeglut
   ```

2. **Compile:**
   ```bash
   g++ -o solarsystem 3D\ solar\ System/*.cpp -lGL -lGLU -lglut -lm
   ```

3. **Run:**
   ```bash
   ./solarsystem
   ```

## Troubleshooting

### Common Issues:

1. **GLUT not found:**
   - Download freeglut from: http://freeglut.sourceforge.net/
   - Place `glut32.lib` in your library path
   - Place `glut.h` in your include path

2. **Texture loading errors:**
   - Ensure all texture files are in the `assets/` directory
   - Check file paths in the code match your directory structure

3. **Build errors in Visual Studio:**
   - Check project properties → Linker → Input → Additional Dependencies
   - Add `opengl32.lib;glu32.lib;glut32.lib`

## Project Configuration

The project is configured for:
- **C++ Standard:** C++20
- **Platform Toolset:** Visual Studio 2022 (v145)
- **Character Set:** Unicode
- **Subsystem:** Console

## Assets

Texture files should be placed in:
- `3D solar System/assets/textures/` - Planet textures
- `3D solar System/assets/skybox/` - Space background

The application loads BMP format textures by default.