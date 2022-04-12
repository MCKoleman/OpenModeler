#include "mesh.h"

void Mesh::CalcBasis()
{
    forward = glm::vec3(
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
    up = glm::cross(right, forward);
}

glm::vec3 Mesh::GetUp()
{
    return up;
}

glm::vec3 Mesh::GetRight()
{
    return right;
}

glm::vec3 Mesh::GetForward()
{
    return forward;
}

void Mesh::Translate(glm::vec3 _deltaPos)
{
    pos += _deltaPos;
}

void Mesh::Rotate(glm::vec3 _deltaRot)
{
    rotation += _deltaRot;
}

void Mesh::Scale(glm::vec3 _deltaScale)
{
    scale = glm::vec3(scale.x * _deltaScale.x, scale.y * _deltaScale.y, scale.z * _deltaScale.z);
}

glm::vec3 Mesh::GetPos()
{
    return pos;
}

glm::vec3 Mesh::GetRotation()
{
    return rotation;
}

glm::vec3 Mesh::GetScale()
{
    return scale;
}

void Mesh::SetPos(glm::vec3 _pos)
{
    pos = _pos;
}

void Mesh::SetRotation(glm::vec3 _rot)
{
    rotation = _rot;
}

void Mesh::SetScale(glm::vec3 _scale)
{
    scale = glm::max(_scale, MIN_SCALE);
}

Mesh::Mesh()
{
    pos = glm::vec3();
}

Mesh::~Mesh()
{

}