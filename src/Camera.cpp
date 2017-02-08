#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

using namespace glm;

Camera* Camera::currentCamera = nullptr;

Camera::Camera(const vec3& vEye,
               const vec3& vCenter,
               const vec3& vUp) :
    eye{vEye},
    center{vCenter},
    up{vUp}
{
    if (!currentCamera) {
        currentCamera = this;
    }
}

Camera* Camera::getCurrentCamera() {
    return currentCamera;
}

mat4 Camera::viewMatrix() {
//    vec3 zaxis = normalize(eye - lookAt);
//    vec3 xaxis = normalize(cross(up, zaxis));
//    vec3 yaxis = cross(zaxis, xaxis);
//
//    mat4 viewM {
//        xaxis.x, yaxis.x, zaxis.x, 0.0,
//        xaxis.y, yaxis.y, zaxis.y, 0.0,
//        xaxis.z, yaxis.z, zaxis.z, 0.0,
//        -dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1.0
//    };
//
//    return viewM;
    return lookAt(eye, center, up);
}
