#ifndef __PHONG_CUBE_H__
#define __PHONG_CUBE_H__

#include <GLES2/gl2.h>
#include "glm/gtc/type_precision.hpp"
#include "glm/fwd.hpp"

class PhongCube {
public:
    PhongCube();
    virtual ~PhongCube();
    virtual void update(unsigned int timeelapsed);
    virtual void draw();
    virtual void draw(const glm::mat4& uber_model);
    virtual void setPosition(float x, float y, float z);
    virtual void setPosition(const glm::vec3& aPosition);
    virtual void setScale(float x, float y, float z);
    virtual void setScale(const glm::vec3& aScale);
    virtual void setRotation(float x, float y, float z, float angle);
    virtual void setRotation(const glm::vec3& aRotationAxis, float angle);
    virtual void setAmbient(float r, float g, float b);
    virtual void setAmbient(const glm::vec3& aAmbient);
    virtual void setDiffuse(float r, float g, float b);
    virtual void setDiffuse(const glm::vec3& aDiffuse);
    virtual void setSpecular(float r, float g, float b, float aShininess);
    virtual void setSpecular(const glm::vec3& aSpecular, float aShininess);
    virtual glm::vec3 getPosition() const {
        return position;
    }
    virtual glm::mat4 getModelMatrix() const;

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
    static GLint ambient_index;
    static GLint diffuse_index;
    static GLint specular_index;
    static GLint shininess_index;
    static GLint light_src_index;

    static GLfloat vertices[];
    static GLfloat normals[];

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotationAxis;
    float rotationAngle;
    GLfloat ambient[3];
    GLfloat diffuse[3];
    GLfloat specular[3];
    GLfloat shininess;
};

#endif // __PHONG_CUBE_H__
