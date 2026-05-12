#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

// ---------------- CAMERA ----------------
float cameraX = 0.0f;
float cameraY = 5.0f;
float cameraZ = 30.0f;
int topView = 0;

// 🔥 PROFESSIONAL ORBIT CAMERA SYSTEM
float cameraAngle = 0.0f;     // left/right rotation around Sun
float cameraRadius = 30.0f;   // distance from Sun

// ---------------- TARGET ----------------
float targetX = 0.0f;
float targetY = 0.0f;
float targetZ = 0.0f;

// 🔥 REQUIRED EXTERNAL PLANET POSITION
extern float planetPos[8][3];

// ---------------- CONTROL ----------------
int paused = 0;
int focusMode = 0;
int focusedPlanet = -1;

// ---------------- CAMERA ORBIT SYSTEM ----------------
void updateCameraOrbit()
{
    if (topView)
    {
        cameraX = 0.0f;
        cameraY = 80.0f;   // 🔥 lower than 80
        cameraZ = 0.1f;
    }
    else
    {
        float rad = cameraAngle * 3.1416f / 180.0f;

        cameraX = cameraRadius * sin(rad);
        cameraZ = cameraRadius * cos(rad);
        cameraY = 10.0f + sin(rad * 0.5f) * 2.0f;
    }
}

// ---------------- TARGET SYSTEM ----------------
void updateCameraTarget()
{
    if (focusMode && focusedPlanet >= 0)
    {
        targetX = planetPos[focusedPlanet][0];
        targetY = planetPos[focusedPlanet][1];
        targetZ = planetPos[focusedPlanet][2];
    }
    else
    {
        targetX = 0.0f;
        targetY = 0.0f;
        targetZ = 0.0f;
    }
}

// ---------------- BMP LOADER ----------------
unsigned char* loadBMP(const char* filename, int* width, int* height)
{
    FILE* file = fopen(filename, "rb");

    if (!file)
    {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("Error: Not a valid BMP file %s\n", filename);
        fclose(file);
        return NULL;
    }

    *width = *(int*)&header[18];
    *height = *(int*)&header[22];

    int size = 3 * (*width) * (*height);

    unsigned char* data = (unsigned char*)malloc(size);
    if (!data)
    {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(data, sizeof(unsigned char), size, file);
    fclose(file);

    for (int i = 0; i < size; i += 3)
    {
        unsigned char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }

    return data;
}

// ---------------- TEXTURE LOADER ----------------
GLuint loadTexture(const char* filename)
{
    int width, height;

    unsigned char* data = loadBMP(filename, &width, &height);

    if (!data)
    {
        printf("Failed to load texture: %s\n", filename);
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
        width, height, 0,
        GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data);

    printf("Texture loaded successfully: %s\n", filename);

    return texture;
}