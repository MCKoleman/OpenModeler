#include "camera.h"

// Calculates the basis of the camera
void Camera::CalcBasis()
{
    dir = glm::vec3(
        cos(rotation.y) * sin(rotation.x),
        sin(rotation.y),
        cos(rotation.y) * cos(rotation.x)
    );

    // Right vector
    right = glm::vec3(
        sin(rotation.x - HALF_PI),
        0,
        cos(rotation.x - HALF_PI)
    );

    // Up vector : perpendicular to both direction and right
    up = glm::cross(right, dir);
}

Camera::Camera()
    : Camera(-45.0f, 0.1f, 100.0f) {}

Camera::Camera(float _fov, float _nearClip, float _farClip)
    : Camera(_fov, _nearClip, _farClip, glm::vec3(-2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) {}

Camera::Camera(float _fov, float _nearClip, float _farClip, glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _up)
    : Camera(_fov, _nearClip, _farClip, _pos, _dir, _up, glm::vec2(), true) {}

Camera::Camera(float _fov, float _nearClip, float _farClip, glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _up, glm::vec2 _orthSize, bool _isPerspective)
    : fov(_fov), nearClip(_nearClip), farClip(_farClip), pos(_pos), dir(_dir), up(_up), orthSize(_orthSize), isPerspective(_isPerspective)
{
    rotation = glm::vec3(PI, 0.0f, 0.0f);
    CalcBasis();
}