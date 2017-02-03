#include <iostream>

#include "util.h"

using namespace std;

GLuint loadShader(const char* shaderSrc, GLenum type){
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    if(shader==0) return 0;

    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    // Check compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled){
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1){
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            cerr << "Error compiling shader:" << endl << infoLog << endl;
            delete infoLog;
        }
        glDeleteShader(shader);
        abort();
        return 0;
    }

    return shader;
}

GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId){
    GLuint programObject;
    GLint linked;
    programObject = glCreateProgram();
    if(programObject == 0){
        cerr << "ERROR: could not create GLSL program." << endl;
        abort();
    }
    glAttachShader(programObject, vertexShaderId);
    glAttachShader(programObject, fragmentShaderId);
    glLinkProgram(programObject);
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if(!linked){
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1){
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            cerr << "ERROR linking program:" << endl << infoLog << endl;
            delete infoLog;
        }
        glDeleteProgram(programObject);
        abort();
    }
    return programObject;
}
