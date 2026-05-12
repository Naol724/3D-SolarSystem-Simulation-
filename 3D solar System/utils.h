#ifndef UTILS_H
#define UTILS_H

#include <GL/glut.h>


// Camera
extern float cameraX, cameraY, cameraZ;
void updateCameraTarget();
extern float targetX, targetY, targetZ;
extern float cameraYaw;
extern float cameraAngle;
extern float cameraRadius;
extern int topView;
// Focus system
extern int focusMode;
extern int focusedPlanet;

// Rocket
extern float rocketX, rocketY, rocketZ;

// Control
extern int paused;

// Planet control (IMPORTANT)
extern int selectedPlanet;
extern float planetSize[8];


// Texture loader
GLuint loadTexture(const char* filename);

#endif