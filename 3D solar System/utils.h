#ifndef UTILS_H
#define UTILS_H

#include <GL/glut.h>

// Camera
extern float cameraX, cameraY, cameraZ;
extern float cameraAngle;

// Target
extern float targetX, targetY, targetZ;

// Focus system
extern int focusMode;
extern int focusedPlanet;

// Controls
extern int paused;

// Planet system
extern int selectedPlanet;
extern float planetSize[8];
extern float planetPos[8][3];

// Texture loader
GLuint loadTexture(const char* filename);

// Camera update functions
void updateCameraOrbit();
void updateCameraTarget();

#endif