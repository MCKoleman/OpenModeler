#include "input.h"

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
bool ProcessInput(GLFWwindow* window, Scene* scene, float deltaTime, SpeedConsts* speeds, int* prevX, int* prevY)
{
    Camera* camera = scene->GetCamera();
    Mesh* mesh = scene->GetCurMesh();
    bool didReceiveInput = false;

    // Get window width and height
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    double halfWidth = width * 0.5f;
    double halfHeight = height * 0.5f;

    // Exit window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return true;
    }

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // Move camera if ctrl is pressed
        if (ALT_PRESS)
            camera->pos += camera->dir * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(mesh->GetForward() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move back
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // Save on Ctrl+S
        if (CTRL_PRESS)
            WriteObjToFile(scene, "../models/", scene->GetCurMesh()->GetName());
        // Move camera if ctrl is pressed
        else if (ALT_PRESS)
            camera->pos -= camera->dir * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(-mesh->GetForward() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        // Move camera if ctrl is pressed
        if (ALT_PRESS)
            camera->pos += camera->right * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(mesh->GetRight() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // Move camera if ctrl is pressed
        if (ALT_PRESS)
            camera->pos -= camera->right * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(-mesh->GetRight() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        // Move camera if ctrl is pressed
        if (ALT_PRESS)
            camera->pos += camera->up * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(mesh->GetUp() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move down
    if (SHIFT_PRESS) {
        // Move camera if ctrl is pressed
        if (ALT_PRESS)
            camera->pos -= camera->up * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(-mesh->GetUp() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }

    // Focus object
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        glm::vec3 targetDir = glm::normalize(mesh->GetPos() - camera->pos);
        float rotY = asin(targetDir.y);
        float rotX = atan2(targetDir.x, targetDir.z);
        camera->rotation = glm::vec3(rotX, rotY, 0.0f);
        camera->CalcBasis();
        didReceiveInput = true;
    }

    // Scale up
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mesh->SetScale(mesh->GetScale() + glm::vec3(speeds->modelScaleRate * deltaTime) * mesh->GetScale());
        didReceiveInput = true;
    }
    // Scale down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        mesh->SetScale(mesh->GetScale() - glm::vec3(speeds->modelScaleRate * deltaTime) * mesh->GetScale());
        didReceiveInput = true;
    }

    // Rotate up
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        // Rotate camera if ctrl is pressed
        if (ALT_PRESS)
            camera->rotation.y += speeds->cameraTurnSpeed * deltaTime;
        // Otherwise rotate model
        else
            mesh->Rotate(glm::vec3(0, 1, 0) * speeds->modelTurnSpeed * deltaTime);
        didReceiveInput = true;
    }
    // Rotate down
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        // Rotate camera if ctrl is pressed
        if (ALT_PRESS)
            camera->rotation.y -= speeds->cameraTurnSpeed * deltaTime;
        // Otherwise rotate model
        else
            mesh->Rotate(glm::vec3(0, -1, 0) * speeds->modelTurnSpeed * deltaTime);
        didReceiveInput = true;
    }
    // Rotate right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        // Rotate camera if ctrl is pressed
        if (ALT_PRESS)
            camera->rotation.x += speeds->cameraTurnSpeed * deltaTime;
        // Otherwise rotate model
        else
            mesh->Rotate(glm::vec3(1, 0, 0) * speeds->modelTurnSpeed * deltaTime);
        didReceiveInput = true;
    }
    // Rotate left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        // Rotate camera if ctrl is pressed
        if (ALT_PRESS)
            camera->rotation.x -= speeds->cameraTurnSpeed * deltaTime;
        // Otherwise rotate model
        else
            mesh->Rotate(glm::vec3(-1, 0, 0) * speeds->modelTurnSpeed * deltaTime);
        didReceiveInput = true;
    }

    // Mouse input
    if (ALT_PRESS && MOUSE_PRESS) {
        // Track mouse movement
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        int xPos = (int)glm::floor(mouseX);
        int yPos = (int)glm::floor(mouseY);

        // Reset previous positions
        if (*prevX < 0)
            *prevX = xPos;
        if (*prevY < 0)
            *prevY = yPos;

        float deltaX = float(*prevX - xPos);
        float deltaY = float(*prevY - yPos);

        // Alt + LMB to rotate
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            // Apply changes to camera
            camera->rotation.x += speeds->mouseTurnSpeed * deltaTime * deltaX;
            camera->rotation.y += speeds->mouseTurnSpeed * deltaTime * deltaY;
        }
        // Alt + RMB to move
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            // Apply changes to camera
            camera->pos += camera->right * speeds->mouseMoveSpeed * deltaTime * deltaX;
            camera->pos += camera->up * speeds->mouseMoveSpeed * deltaTime * deltaY;
        }

        // Keep mouse where it was clicked
        glfwSetCursorPos(window, (float)(*prevX), (float)(*prevY));
        didReceiveInput = true;
    }
    // Reset previous click location when there 
    else {
        *prevX = -1;
        *prevY = -1;
    }

    // Recalculate camera basis if any input was received
    if (didReceiveInput) {
        camera->CalcBasis();
        mesh->CalcBasis();
    }

    return didReceiveInput;
}