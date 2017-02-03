#ifndef __TESTCUBE_H__
#define __TESTCUBE_H__

#include <GLES2/gl2.h>

class TestCube{
public:
    TestCube();
    virtual ~TestCube();
    virtual void update(unsigned int timeelapsed);
    virtual void draw();
private:
    static unsigned int testCubeCounter;
    static GLuint vertexShaderId;
    static GLuint fragmentShaderId;
    static GLuint programObject;
    static GLint v_pos_index;
    static GLint v_color_index;
    static GLint mvp_matrix_index;
    static GLfloat vertices[];
    static GLfloat colors[];

    float angle;
};

#endif // __TESTCUBE_H__
