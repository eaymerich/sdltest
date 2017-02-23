#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera {
public:
    Camera(const glm::vec3& vEye    = glm::vec3{0.0,0.0,1.0},
           const glm::vec3& vCenter = glm::vec3{0.0,0.0,0.0},
           const glm::vec3& vUp     = glm::vec3{0.0,1.0,0.0});
    virtual ~Camera() = default;
    static Camera* getCurrentCamera();
    static void setCurrentCamera(Camera* aCamera);
    static void setCurrentCamera(Camera& aCamera);
    virtual void update();
    virtual glm::mat4& viewMatrix();
    virtual glm::mat4& projMatrix();

protected:
    static Camera* currentCamera;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::mat4 viewM;
    glm::mat4 projM;
};

#endif // __CAMERA_H__
