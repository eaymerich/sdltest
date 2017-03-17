#include "PhongStaticCube.h"

PhongStaticCube::PhongStaticCube() :
    modelMatrix{1.0f}
{}

glm::mat4 PhongStaticCube::getModelMatrix() const {
    return modelMatrix;
}

void PhongStaticCube::applyChangesIntoModelMatrix() {
    modelMatrix = PhongCube::getModelMatrix();
}
