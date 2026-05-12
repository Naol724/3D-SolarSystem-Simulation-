#include <stdlib.h>
#include <GL/glut.h>
#include "input.h"
#include "utils.h"
#include "solarsystem.h"
#include <math.h>

// external variables
extern float cameraRadius;
extern float cameraAngle;
extern int paused;
extern int focusMode;
extern int selectedPlanet;
extern float planetSize[8];
extern float rocketX, rocketY, rocketZ;
extern int topView;

void handleKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        cameraRadius -= 2.0f;   // zoom in
        if (cameraRadius < 5.0f)
            cameraRadius = 5.0f;
        break;

    case 's':
        cameraRadius += 2.0f;   // zoom out
        break;

    case 'a':
        cameraAngle -= 2.0f;   // rotate left
        break;

    case 'd':
        cameraAngle += 2.0f;   // rotate right
        break;

    case ' ':
        paused = !paused;
        break;

    case 'r':
        cameraAngle = 0.0f;
        cameraRadius = 30.0f;
        break;

    case 'f':
        focusMode = !focusMode;
        break;

    case 't':
    case 'T':
        topView = !topView;
        break;

    case 'q':
        exit(0);
        break;

    case 'i': rocketZ -= 1.0f; break;
    case 'k': rocketZ += 1.0f; break;
    case 'j': rocketX -= 1.0f; break;
    case 'l': rocketX += 1.0f; break;

    case 'n':
        selectedPlanet = (selectedPlanet + 1) % 8;
        break;

    case 'b':
        selectedPlanet = (selectedPlanet - 1 + 8) % 8;
        break;

    case 'u':
        planetSize[selectedPlanet] += 0.1f;
        break;

    case 'v':
        if (planetSize[selectedPlanet] > 0.1f)
            planetSize[selectedPlanet] -= 0.1f;
        break;
    
    }

    glutPostRedisplay();
}