#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "solarsystem.h"
#include "utils.h"

float sunPulse = 0.0f;

int selectedPlanet = 0;
float planetPos[8][3];

float cameraDistance = 30.0f;

// ---------------- PLANET SIZE CONTROL ----------------
float planetSize[] = {
    0.4f, 0.6f, 0.7f, 0.5f,
    0.3f, 0.5f, 0.5f, 0.6f
};

const char* planetNames[] = {
    "Mercury","Venus","Earth","Mars",
    "Jupiter","Saturn","Uranus","Neptune"
};

float mercurySpeed = 1.59f;
float venusSpeed = 1.17f;
float earthSpeed = 1.00f;
float marsSpeed = 0.81f;
float jupiterSpeed = 0.44f;
float saturnSpeed = 0.33f;
float uranusSpeed = 0.23f;
float neptuneSpeed = 0.18f;

// ---------------- ORBIT TILTS ----------------
float mercuryTilt = 7;
float venusTilt = 3;
float earthTilt = 0;
float marsTilt = 1.85;
float jupiterTilt = 1.3;
float saturnTilt = 2.5;
float uranusTilt = 0.8;
float neptuneTilt = 1.8;

// ---------------- EXTERNAL ----------------
extern float cameraX, cameraY, cameraZ;
extern int paused;

float planetDist[] = { 5,7,10,14,18,22,26,30 };

// ---------------- SKYBOX ----------------
void drawSkybox();

// ---------------- ANGLES ----------------
float mercuryOrbit = 0, venusOrbit = 0, earthOrbit = 0, marsOrbit = 0;
float jupiterOrbit = 0, saturnOrbit = 0, uranusOrbit = 0, neptuneOrbit = 0;

float mercuryRotate = 0, venusRotate = 0, earthRotate = 0, marsRotate = 0;
float jupiterRotate = 0, saturnRotate = 0, uranusRotate = 0, neptuneRotate = 0;

float moonOrbit = 0;

// ---------------- ROCKET & UFO ----------------
float rocketX = 0, rocketY = 0, rocketZ = 20;
float ufoAngle = 0;
float ufoRadius = 15;

// ---------------- TEXTURES ----------------
GLuint sunTex, mercuryTex, venusTex, earthTex, marsTex;
GLuint jupiterTex, saturnTex, uranusTex, neptuneTex;
GLuint skyTex;

// ---------------- STARS ----------------
#define STAR_COUNT 1000
float stars[STAR_COUNT][3];

// ---------------- TEXT ----------------
void drawText(float x, float y, float z, const char* text)
{
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (int i = 0; text[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

    glEnable(GL_LIGHTING);
}

// ---------------- STARS ----------------
void initStars()
{
    for (int i = 0;i < STAR_COUNT;i++) {
        stars[i][0] = rand() % 400 - 200;
        stars[i][1] = rand() % 400 - 200;
        stars[i][2] = rand() % 400 - 200;
    }
}

void drawStars()
{
    glDisable(GL_LIGHTING);
    glPointSize(2);

    glBegin(GL_POINTS);
    for (int i = 0;i < STAR_COUNT;i++)
        glVertex3f(stars[i][0], stars[i][1], stars[i][2]);
    glEnd();

    glEnable(GL_LIGHTING);
}

// ---------------- SKYBOX ----------------
void drawSkybox()
{
    glPushMatrix();

    // 🔥 Skybox must not move with camera
    glTranslatef(cameraX, cameraY, cameraZ);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyTex);

    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);

    // 🔥 Flip normals (inside view)
    gluQuadricOrientation(q, GLU_INSIDE);

    gluSphere(q, 200, 60, 60);

    gluDeleteQuadric(q);

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
}
void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ---------------- SUN POSITION ----------------
    GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    // ---------------- REALISTIC SPACE AMBIENT ----------------
    GLfloat ambient[] = { 0.25f, 0.22f, 0.18f, 1.0f };
    // ---------------- WARM SUNLIGHT (YELLOW-ORANGE) ----------------
    GLfloat diffuse[] = { 1.0f, 0.95f, 0.8f, 1.0f };
    // ---------------- STRONG SPECULAR HIGHLIGHT ----------------
    GLfloat specular[] = { 1.0f, 1.0f, 0.9f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // ---------------- LIGHT ATTENUATION (IMPORTANT FOR REALISM) ----------------
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01);     // 🔥 reduced
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.001); // 🔥 soft falloff

    // ---------------- MATERIAL RESPONSE ----------------
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // ---------------- SMOOTH LIGHTING ----------------
    glShadeModel(GL_SMOOTH);
}
// ---------------- SPHERE ----------------
void drawSphere(GLuint tex, float r)
{
    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    gluSphere(q, r, 40, 40);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(q);
}

// ---------------- ORBIT ----------------
void drawOrbit(float r)
{
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < 360;i++) {
        float a = i * 3.1416 / 180;
        glVertex3f(r * cos(a), 0, r * sin(a));
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

void drawSaturnRing(float innerRadius, float outerRadius)
{
    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i <= 361; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        float c = cos(angle);
        float s = sin(angle);

        glVertex3f(innerRadius * c, 0.0f, innerRadius * s);
        glVertex3f(outerRadius * c, 0.0f, outerRadius * s);
    }

    glEnd();
}

// ---------------- SUN ----------------
void drawSun()
{
    glPushMatrix();

    // ---------------- PULSE ----------------
    float pulse = 1.0f + 0.05f * sin(sunPulse);

    // ---------------- LIGHT SOURCE ----------------
    GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // ---------------- ENABLE BLENDING FOR GLOW ----------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // ---------------- OUTER GLOW ----------------
    glDisable(GL_LIGHTING);
    for (int i = 0; i < 6; i++)
    {
        float scale = (3.0f + i * 0.6f) * pulse;
        float alpha = 0.15f / (i + 1);

        glColor4f(1.0f, 0.6f, 0.1f, alpha);
        glutSolidSphere(scale, 40, 40);
    }

    // ---------------- SUN CORE (TEXTURED) ----------------
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sunTex);

    GLfloat emission[] = { 1.0f, 0.8f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(2.5f * pulse, 60, 60);

    GLfloat noEmission[] = { 0,0,0,1 };
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glDisable(GL_TEXTURE_2D);

    // ---------------- LABEL ----------------
    drawText(0, 4.0, 0, "Sun");

    glPopMatrix();
}

// ---------------- PLANET ----------------
void drawPlanet(GLuint tex, float orbit, float rot, float dist,
    float size, float tilt, const char* name, int index)
{
    drawOrbit(dist);

    glPushMatrix();

    glRotatef(orbit, 0, 1, 0);      // orbit movement
    glRotatef(tilt, 0, 0, 1);       // tilt
    glTranslatef(dist, 0, 0);       // move outward

    // ✅ NOW capture position correctly
    planetPos[index][0] = dist * cos(orbit * 3.1416 / 180);
    planetPos[index][1] = 0;
    planetPos[index][2] = dist * sin(orbit * 3.1416 / 180);

    drawText(0, size + 0.6, 0, name);

    glRotatef(rot, 0, 1, 0);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 30.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    drawSphere(tex, size);

    glPopMatrix();
}

// ---------------- EARTH ----------------
void drawEarth()
{
    drawOrbit(10);

    glPushMatrix();
    glRotatef(earthOrbit, 0, 1, 0);
    glTranslatef(10, 0, 0);

    drawText(0, 1.5, 0, "Earth");

    glPushMatrix();
    glRotatef(earthRotate, 0, 1, 0);
    drawSphere(earthTex, planetSize[2]);
    glPopMatrix();

    glPushMatrix();
    glRotatef(moonOrbit, 0, 1, 0);
    glTranslatef(2, 0, 0);

    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

// ---------------- ROCKET ----------------
void drawRocket()
{
    glPushMatrix();
    glTranslatef(rocketX, rocketY, rocketZ);

    glColor3f(1, 1, 1);
    glutSolidCube(1);

    glTranslatef(0, 1, 0);
    glColor3f(1, 0.2, 0.2);
    glutSolidCone(0.5, 1, 20, 20);

    glPopMatrix();
}

// ---------------- UFO ----------------
void drawUFO()
{
    glPushMatrix();

    float x = cos(ufoAngle) * ufoRadius;
    float z = sin(ufoAngle) * ufoRadius;

    glTranslatef(x, 6, z);

    glColor3f(0.4, 1, 0.4);
    glutSolidSphere(0.8, 30, 30);

    glTranslatef(0, 0.5, 0);
    glColor3f(0.2, 0.8, 1);
    glutSolidSphere(0.4, 30, 30);

    glPopMatrix();
}

// ---------------- UPDATE (REALISTIC MOTION) ----------------
void updateSolarSystem()
{
    if (!paused)
    {
        mercuryOrbit += mercurySpeed;
        venusOrbit += venusSpeed;
        earthOrbit += earthSpeed;
        marsOrbit += marsSpeed;
        jupiterOrbit += jupiterSpeed;
        saturnOrbit += saturnSpeed;
        uranusOrbit += uranusSpeed;
        neptuneOrbit += neptuneSpeed;

        mercuryRotate += 2;
        venusRotate += 2;
        earthRotate += 2;
        marsRotate += 2;
        jupiterRotate += 2;
        saturnRotate += 2;
        uranusRotate += 2;
        neptuneRotate += 2;

        moonOrbit += 2;
        ufoAngle += 0.02;

        sunPulse += 0.05f;

        rocketX += 0.05;
        rocketZ -= 0.03;

        if (rocketZ < -50) {
            rocketZ = 20;
            rocketX = 0;
        }
    }
}

// ---------------- DRAW SYSTEM ----------------
void drawSolarSystem()
{
    // ---------------- SKY & BACKGROUND ----------------
    drawSkybox();
    drawStars();

    glEnable(GL_NORMALIZE);

    // ---------------- PLANETS (UNCHANGED) ----------------
    drawPlanet(mercuryTex, mercuryOrbit, mercuryRotate, 5, planetSize[0], mercuryTilt, "Mercury", 0);
    drawPlanet(venusTex, venusOrbit, venusRotate, 7, planetSize[1], venusTilt, "Venus", 1);

    drawEarth();

    drawPlanet(marsTex, marsOrbit, marsRotate, 14, planetSize[3], marsTilt, "Mars", 2);
    drawPlanet(jupiterTex, jupiterOrbit, jupiterRotate, 18, planetSize[4], jupiterTilt, "Jupiter", 3);

    // ---------------- ☀️ REALISTIC TOMATO SUN (FIXED) ----------------

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // keep sun at center

    // Sun glow (emission)
    GLfloat emission[] = { 1.0f, 0.35f, 0.15f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    // Sun color (surface)
    glColor3f(1.0f, 0.4f, 0.2f);

    // Draw sun
    glutSolidSphere(2.8, 60, 60);

    // Reset emission
    GLfloat noEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);

    glPopMatrix();

    // ---------------- ORBITS ----------------
    drawOrbit(22);

    glPushMatrix();

    // Saturn orbit movement
    glRotatef(saturnOrbit, 0, 1, 0);
    glTranslatef(22, 0, 0);

    // ================= RING FIRST =================
    glPushMatrix();

    glRotatef(25, 1, 0, 0);

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    drawSaturnRing(
        planetSize[5] + 0.4f,
        planetSize[5] + 1.5f
    );

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    // ================= SATURN PLANET =================
    glPushMatrix();
    glRotatef(saturnRotate, 0, 1, 0);
    drawSphere(saturnTex, planetSize[5]);
    glPopMatrix();

    glPopMatrix();

    // ---------------- OUTER PLANETS ----------------
    drawPlanet(uranusTex, uranusOrbit, uranusRotate, 26, planetSize[6], uranusTilt, "Uranus", 5);
    drawPlanet(neptuneTex, neptuneOrbit, neptuneRotate, 30, planetSize[7], neptuneTilt, "Neptune", 6);

    // ---------------- OBJECTS ----------------
    drawRocket();
    drawUFO();

    // ---------------- UI TEXT ----------------
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 0);

    char info[100];
    sprintf(info, "Selected: %s", planetNames[selectedPlanet]);

    glRasterPos3f(-5, 10, -10);
    for (int i = 0; info[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, info[i]);

    glEnable(GL_LIGHTING);
    glPopMatrix();
}
// ---------------- INIT ----------------
void initSolarSystem()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    setupLighting();
    initStars();
    

    sunTex = loadTexture("assets/skybox/sun3.bmp");
    mercuryTex = loadTexture("assets/textures/mercury.bmp");
    venusTex = loadTexture("assets/textures/venus.bmp");
    earthTex = loadTexture("assets/textures/earth.bmp");
    marsTex = loadTexture("assets/textures/mars.bmp");
    jupiterTex = loadTexture("assets/textures/jupiter.bmp");
    saturnTex = loadTexture("assets/textures/saturn.bmp");
    uranusTex = loadTexture("assets/textures/uranus.bmp");
    neptuneTex = loadTexture("assets/textures/neptune.bmp");

    skyTex = loadTexture("assets/skybox/skybox1.bmp");
}