#ifndef __UTIL_H__
#define __UTIL_H__

#include <GLES2/gl2.h>

GLuint loadShader(const char* shaderSrc, GLenum type);
GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId);

#endif // __UTIL_H__
