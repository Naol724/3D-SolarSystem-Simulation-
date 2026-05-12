#ifndef SHADER_H
#define SHADER_H

#include <GL/glut.h>

// shader loader
GLuint loadShader(const char* vertexPath, const char* fragmentPath);

// activate shader
void useShader(GLuint program);

#endif