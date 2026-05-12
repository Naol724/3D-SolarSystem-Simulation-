#include <GL/glut.h>
#include <stdio.h>

#include "solarsystem.h"
#include "input.h"
#include "utils.h"

// ---------------- DISPLAY ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 🔥 UPDATE CAMERA SYSTEM (IMPORTANT FIX)
    updateCameraOrbit();
    updateCameraTarget();

    // ---------------- CAMERA ----------------
    gluLookAt(
        cameraX, cameraY, cameraZ,
        targetX, targetY, targetZ,
        0.0f, 1.0f, 0.0f
    );

    // ---------------- DRAW SCENE ----------------
    drawSolarSystem();

    glutSwapBuffers();
}

// ---------------- TIMER ----------------
void timer(int value)
{
    updateSolarSystem();   // planets movement

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ---------------- RESHAPE ----------------
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)w / (float)h, 1.0, 300.0);

    glMatrixMode(GL_MODELVIEW);
}

// ---------------- MAIN ----------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(900, 600);
    glutCreateWindow("3D Solar System - Group 9");

    initSolarSystem();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyboard);

    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}