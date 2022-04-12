#include "openHelper.h"

// Calculates the model view perspective matrix
// --------------------------------------------
glm::mat4 CalcMVP(Camera* camera, Mesh* mesh)
{
    return GetProjectionMatrix(camera) * GetViewMatrix(camera) * GetModelMatrix(mesh);
}

// Returns the projection matrix of the given camera
glm::mat4 GetProjectionMatrix(Camera* camera)
{
    // Projection
    glm::mat4 projection = glm::mat4(1.0f);

    // Perspective projection
    if ((*camera).isPerspective) {
        projection = glm::perspective(glm::radians((*camera).fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, (*camera).nearClip, (*camera).farClip);
    }
    // Orthographic projection
    else {
        glm::mat4 projection = glm::ortho(-(*camera).orthSize.x, (*camera).orthSize.x, -(*camera).orthSize.y, (*camera).orthSize.y,
            (*camera).nearClip, (*camera).farClip);
    }

    return projection;
}

// Returns the view matrix of the given camera
glm::mat4 GetViewMatrix(Camera* camera)
{
    // Camera view
    return glm::lookAt((*camera).pos, (*camera).pos + (*camera).dir, (*camera).up);
}

// Returns the model matrix of the given mesh
glm::mat4 GetModelMatrix(Mesh* mesh)
{
    // Model position
    glm::vec3 scale = mesh->GetScale();
    glm::vec3 rotation = mesh->GetRotation();
    glm::vec3 position = mesh->GetPos();
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(0, 1, 0));
    glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(1, 0, 0));
    glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));

    glm::mat4 modelRotated = rotateZ * rotateY * rotateX * translate;
    glm::mat4 modelUnscaled = glm::translate(modelRotated, position);
    return glm::scale(modelUnscaled, scale);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}