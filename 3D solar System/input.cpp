#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "utils.h"
#include "solarsystem.h"

void handleKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        cameraZ -= 1.0f;
        break;

    case 's':
        cameraZ += 1.0f;
        break;

    case 'a':
        cameraX -= 1.0f;
        break;

    case 'd':
        cameraX += 1.0f;
        break;

    case ' ':
        paused = !paused;
        break;

    case 'r':
        cameraX = 0;
        cameraY = 10;
        cameraZ = 30;
        cameraAngle = 0;
        break;

        // ⭐ FIXED: focus planets properly
    case '1': focusedPlanet = 0; focusMode = 1; break;
    case '2': focusedPlanet = 1; focusMode = 1; break;
    case '3': focusedPlanet = 2; focusMode = 1; break;
    case '4': focusedPlanet = 3; focusMode = 1; break;
    case '5': focusedPlanet = 4; focusMode = 1; break;
    case '6': focusedPlanet = 5; focusMode = 1; break;
    case '7': focusedPlanet = 6; focusMode = 1; break;
    case '8': focusedPlanet = 7; focusMode = 1; break;

    case '0':
        focusMode = 0;
        break;

    case 'q':
        exit(0);
        break;
    }

    glutPostRedisplay();
}