#ifndef SHADER_H
#define SHADER_H

#include <GL/glut.h>

GLuint loadShader(const char* vertexPath, const char* fragmentPath);
void useShader(GLuint program);

#endif