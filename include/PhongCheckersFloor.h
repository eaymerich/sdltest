#ifndef PHONGCHECKERSFLOOR_H
#define PHONGCHECKERSFLOOR_H

#include <GLES2/gl2.h>
#include "glm/gtc/type_precision.hpp"
#include "glm/fwd.hpp"

class PhongCheckersFloor {
public:
    PhongCheckersFloor();
    virtual ~PhongCheckersFloor();
    virtual void draw();

protected:
    virtual void loadShaders();
    virtual void unLoadShaders();

private:
    static unsigned int instanceCounter;
    static GLuint vertexShaderId;
    static GLuint fragmentShaderId;
    static GLuint programObject;
    static GLint v_pos_index;
    static GLint model_matrix_index;
    static GLint view_matrix_index;
    static GLint projection_matrix_index;
    static GLint ambient_index;
    static GLint diffuse_index;
    static GLint specular_index;
    static GLint shininess_index;
    static GLint light_src_index;

    static GLfloat vertices[];

    GLfloat ambient[3];
    GLfloat specular[3];
    GLfloat shininess;
};

#endif // PHONGCHECKERSFLOOR_H
