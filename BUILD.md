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
   - The updated code uses:
     - Sun texture: `assets/skybox/sun3.bmp`
     - Skybox texture: `assets/skybox/skybox1.bmp`

3. **Build errors in Visual Studio:**
   - Check project properties → Linker → Input → Additional Dependencies
   - Add `opengl32.lib;glu32.lib;glut32.lib`

4. **Shader files are empty:**
   - The shader system is currently a placeholder
   - The project works without shaders using fixed-function pipeline
   - Empty shader files can be safely ignored

## Project Configuration

The project is configured for:
- **C++ Standard:** C++20
- **Platform Toolset:** Visual Studio 2022 (v145)
- **Character Set:** Unicode
- **Subsystem:** Console

## Assets

Texture files should be placed in:
- `3D solar System/assets/textures/` - Planet textures
- `3D solar System/assets/skybox/` - Space background and sun textures

The application loads BMP format textures by default.

## New Features in Updated Version

The updated version includes:
- Top view camera mode (T key)
- Planet size adjustment (U/V keys)
- Improved sun rendering with pulsing animation
- Enhanced camera controls (W/S for zoom, A/D for rotation)
- Rocket movement controls (I/K/J/L keys)
- Better skybox rendering that moves with camera
- Improved lighting system

## Running the Application

After building, run the application and use:
- **W/S** to zoom in/out
- **A/D** to rotate camera
- **T** to toggle top view
- **F** to toggle focus mode
- **N/B** to cycle through planets
- **U/V** to adjust planet size
- **Space** to pause/resume animation