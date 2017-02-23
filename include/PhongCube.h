#ifndef __PHONGCUBE_H__
#define __PHONGCUBE_H__

#include <GLES2/gl2.h>

class PhongCube {
public:
    PhongCube();
    virtual ~PhongCube();
    virtual void update(unsigned int timeelapsed);
    virtual void draw();

private:
    static unsigned int phongCubeCounter;
    static GLuint vertexShaderId;
    static GLuint fragmentShaderId;
    static GLuint programObject;
    static GLint v_pos_index;
    static GLint v_norm_index;
    static GLint model_matrix_index;
    static GLint view_matrix_index;
    static GLint projection_matrix_index;
    static GLint normal_matrix_index;
    static GLint diffuse_index;
    static GLint specular_index;
    static GLint shininess_index;
    static GLint light_src_index;


    static GLfloat diffuse[];
    static GLfloat specular[];
    static GLfloat shininess;

    static GLfloat vertices[];
    static GLfloat normals[];

    float angle;
};

#endif // __PHONGCUBE_H__
