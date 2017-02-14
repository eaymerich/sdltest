#ifndef __FLATCUBE_H__
#define __FLATCUBE_H__

#include <GLES2/gl2.h>

class FlatCube
{
public:
    FlatCube();
    virtual ~FlatCube();
    virtual void update(unsigned int timeelapsed);
    virtual void draw();

private:
    static unsigned int flatCubeCounter;
    static GLuint vertexShaderId;
    static GLuint fragmentShaderId;
    static GLuint programObject;
    static GLint v_pos_index;
    static GLint v_color_index;
    static GLint model_matrix_index;
    static GLint view_matrix_index;
    static GLint projection_matrix_index;
    static GLfloat vertices[];
    static GLfloat colors[];

    float angle;
};

#endif // __FLATCUBE_H__
