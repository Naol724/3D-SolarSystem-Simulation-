#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "solarsystem.h"
#include "input.h"
#include "utils.h"

// ---------------- EXTERNAL VARIABLES ----------------
extern float cameraX, cameraY, cameraZ;
extern float planetPos[8][3];
extern int selectedPlanet;
extern int focusMode;
extern float cameraAngle;
extern int topView;

void updateCameraOrbit();

// ---------------- DISPLAY ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ---------------- CAMERA UPDATE ----------------
    updateCameraOrbit();

    float targetX = 0.0f;
    float targetY = 0.0f;
    float targetZ = 0.0f;

    if (focusMode)
    {
        targetX = planetPos[selectedPlanet][0];
        targetY = planetPos[selectedPlanet][1];
        targetZ = planetPos[selectedPlanet][2];

        gluLookAt(cameraX, cameraY, cameraZ,
            targetX, targetY, targetZ,
            0.0f, 1.0f, 0.0f);
    }
    else
    {
        gluLookAt(cameraX, cameraY, cameraZ,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f);
    }

    // ---------------- LIGHT SETUP (FIXED SUN LIGHT) ----------------
    GLfloat sunDiffuse[] = { 1.0f, 0.95f, 0.8f, 1.0f };
    GLfloat sunSpecular[] = { 1.0f, 1.0f, 0.9f, 1.0f };
    GLfloat sunAmbient[] = { 0.25f, 0.22f, 0.18f, 1.0f };

    GLfloat lightPos[] = { 0.0f, topView ? 100.0f : 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);

    // ---------------- DRAW SOLAR SYSTEM ----------------
    drawSolarSystem();

    glutSwapBuffers();
}

// ---------------- TIMER ----------------
void timer(int value)
{
    updateSolarSystem();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ---------------- RESHAPE ----------------
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)w / (float)h, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
}

// ---------------- MAIN ----------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Solar System");

    initSolarSystem();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyboard);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}