#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera {
public:
    Camera(const glm::vec3& vEye    = glm::vec3{0.0,0.0,-1.0},
           const glm::vec3& vCenter = glm::vec3{0.0,0.0,0.0},
           const glm::vec3& vUp     = glm::vec3{0.0,1.0,0.0});
    virtual ~Camera() = default;
    static Camera* getCurrentCamera();
    virtual glm::mat4 viewMatrix();

protected:
    static Camera* currentCamera;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
};

#endif // __CAMERA_H__
