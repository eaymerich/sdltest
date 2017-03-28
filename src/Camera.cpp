#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "Time.h"

using namespace glm;

Camera* Camera::currentCamera = nullptr;

Camera::Camera(const vec3& vEye,
               const vec3& vCenter,
               const vec3& vUp) :
    eye{vEye},
    center{vCenter},
    up{vUp},
    viewM{1.0f},
    projM{1.0f}
{
    if (!currentCamera) {
        currentCamera = this;
    }
    projM = perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
}

Camera* Camera::getCurrentCamera() {
    return currentCamera;
}

void Camera::setCurrentCamera(Camera* aCamera) {
    currentCamera = aCamera;
    currentCamera->update();
}

void Camera::setCurrentCamera(Camera& aCamera) {
    currentCamera = &aCamera;
    currentCamera->update();
}

void Camera::update() {
    viewM = lookAt(eye, center, up);
}

mat4& Camera::viewMatrix() {
    return viewM;
}

mat4& Camera::projMatrix() {
    return projM;
}
