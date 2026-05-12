# 3D Solar System Simulation

A real-time 3D solar system simulation built with OpenGL and C++. This project features realistic planetary orbits, textures, lighting, and interactive camera controls.

## Features

- **Realistic Planetary Motion**: Each planet orbits the Sun with accurate relative speeds
- **High-Quality Textures**: Detailed planet textures for all 8 planets and the Sun
- **Interactive Camera**: Orbit around the solar system with keyboard controls
- **Focus Mode**: Zoom in on individual planets by pressing number keys (1-8)
- **Dynamic Lighting**: Realistic lighting with the Sun as the light source
- **Saturn's Rings**: Special rendering for Saturn's distinctive rings
- **Additional Objects**: Rocket and UFO animations
- **Starfield Background**: Thousands of stars in the background
- **Pause/Resume**: Spacebar to pause/resume planetary motion

## Controls

- **W/A/S/D**: Move camera
- **Space**: Pause/resume simulation
- **R**: Reset camera to default position
- **1-8**: Focus on specific planet (Mercury to Neptune)
- **0**: Exit focus mode (return to Sun view)
- **Q**: Quit application

## Project Structure

```
3D Solar System/
├── main.cpp              # Main application entry point
├── solarsystem.cpp/h     # Solar system rendering and logic
├── input.cpp/h          # Keyboard input handling
├── utils.cpp/h          # Utility functions (camera, textures)
├── assets/
│   ├── textures/        # Planet texture images (.bmp, .jpg)
│   └── skybox/          # Space background texture
├── 3D solar System.vcxproj  # Visual Studio project file
└── 3D solar System.slnx     # Solution file
```

## Building the Project

### Prerequisites
- Visual Studio 2019 or later
- OpenGL libraries
- GLUT (OpenGL Utility Toolkit)

### Build Instructions
1. Open `3D solar System.slnx` in Visual Studio
2. Build the solution (Ctrl+Shift+B)
3. Run the application (F5)

## Dependencies

- **OpenGL**: Graphics rendering
- **GLUT**: Window management and input handling
- **Standard C++ Library**: C++20 standard

## Textures

The project includes texture files for:
- Sun (2 variations)
- All 8 planets (Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune)
- Space background for skybox

## Technical Details

- **Rendering**: Uses OpenGL immediate mode with texture mapping
- **Lighting**: Single light source (Sun) with ambient, diffuse, and specular components
- **Camera System**: Orbit camera with smooth movement and focus targeting
- **Animation**: Real-time update loop at ~60 FPS
- **Coordinate System**: Right-handed coordinate system with Y-up

## License

This project is for educational purposes. Texture images may have their own licensing terms.

## Credits

Developed as a computer graphics project. Textures sourced from various astronomy resources.