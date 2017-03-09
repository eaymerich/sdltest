#ifndef __PHONGCUBE_H__
#define __PHONGCUBE_H__

#include <GLES2/gl2.h>
#include "glm/fwd.hpp"
#include "glm/gtc/type_precision.hpp"

class PhongCube {
public:
    PhongCube();
    virtual ~PhongCube();
    virtual void update(unsigned int timeelapsed);
    virtual void draw() const;

private:
    virtual glm::mat4 getModelMatrix() const;
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
    static GLint ambient_index;
    static GLint diffuse_index;
    static GLint specular_index;
    static GLint shininess_index;
    static GLint light_src_index;

    static GLfloat vertices[];
    static GLfloat normals[];

    glm::vec3 position;
    glm::vec3 scale;
    GLfloat ambient[3];
    GLfloat diffuse[3];
    GLfloat specular[3];
    GLfloat shininess;
    float angle;
};

#endif // __PHONGCUBE_H__
