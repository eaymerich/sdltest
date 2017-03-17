#ifndef __PHONG_STATIC_CUBE_H__
#define __PHONG_STATIC_CUBE_H__

#include "PhongCube.h"


class PhongStaticCube : public PhongCube {
public:
    PhongStaticCube();
    virtual ~PhongStaticCube() = default;
    virtual glm::mat4 getModelMatrix() const override;
    virtual void applyChangesIntoModelMatrix();

private:
    glm::mat4 modelMatrix;
};

#endif // __PHONG_STATIC_CUBE_H__
