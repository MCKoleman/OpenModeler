#include "input.h"

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
bool ProcessInput(GLFWwindow* window, Scene* scene, Selection* sel, InputLocks* locks, float deltaTime, SpeedConsts* speeds, int* prevX, int* prevY)
{
    // TODO: Replace mesh reference with proper reference
    Camera* camera = scene->GetCamera();
    Mesh* mesh = scene->GetMeshes()->GetAll().begin()->second;
    bool didReceiveInput = false;

    // Get window width and height
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    double halfWidth = width * 0.5f;
    double halfHeight = height * 0.5f;



    /* ==================================================== Window Stuff ===================================================== */
    // Exit window
    if (ESC_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return true;
    }
    // Focus object
    if (F_PRESS && !CTRL_PRESS) {
        // Only focus when not locked
        if (!locks->lockF) {
            glm::vec3 targetDir = glm::normalize(mesh->GetPos() - camera->pos);
            float rotY = asin(targetDir.y);
            float rotX = atan2(targetDir.x, targetDir.z);
            camera->rotation = glm::vec3(rotX, rotY, 0.0f);
            camera->CalcBasis();

            locks->lockF = true;
        }
        didReceiveInput = true;
    }



    /* ==================================================== Tool Selection ===================================================== */
    // Select selection tool
    if (Q_PRESS && !CTRL_PRESS && !locks->lockQ) {
        sel->SetTool(Tool::SELECT);
        locks->LockTool(Tool::SELECT);
        didReceiveInput = true;
    }
    // Select scale tool
    else if (E_PRESS && !CTRL_PRESS && !locks->lockE) {
        sel->SetTool(Tool::SCALE);
        locks->LockTool(Tool::SCALE);
        didReceiveInput = true;
    }
    // Select extrude tool
    else if (E_PRESS && CTRL_PRESS && !locks->lockCtrlE) {
        sel->SetTool(Tool::EXTRUDE);
        locks->LockTool(Tool::EXTRUDE);
        didReceiveInput = true;
    }
    // Select rotate tool
    else if (R_PRESS && !CTRL_PRESS && !locks->lockR) {
        sel->SetTool(Tool::ROTATE);
        locks->LockTool(Tool::ROTATE);
        didReceiveInput = true;
    }
    // Select move tool
    else if (T_PRESS && !CTRL_PRESS && !locks->lockT) {
        sel->SetTool(Tool::MOVE);
        locks->LockTool(Tool::MOVE);
        didReceiveInput = true;
    }



    /* ==================================================== Keyboard Input ===================================================== */
    /* =================================== Handle movement input ================================== */
    if (WASDZX_PRESS && !CTRL_PRESS) {
        glm::vec3 inputVec = GetWASDZX(window);

        // Only move camera on ALT
        if (ALT_PRESS) {
            camera->pos += inputVec.x * camera->dir * deltaTime * speeds->cameraMoveSpeed;
            camera->pos += inputVec.y * camera->right * deltaTime * speeds->cameraMoveSpeed;
            camera->pos += inputVec.z * camera->up * deltaTime * speeds->cameraMoveSpeed;
        }
        // Handle tools on any other input
        else {
            switch (sel->GetTool()) {
        /* ========== Handle extruding ============== */
            case Tool::EXTRUDE:
                // TODO:
                // Add extrude tool
                break;
        /* ========== Handle moving ================= */
            case Tool::MOVE:
                switch (sel->GetSelMode()) {
                case SelMode::MESH:
                    mesh->Translate(inputVec.x * mesh->GetForward() * deltaTime * speeds->modelMoveSpeed);
                    mesh->Translate(inputVec.y * mesh->GetRight() * deltaTime * speeds->modelMoveSpeed);
                    mesh->Translate(inputVec.z * mesh->GetUp() * deltaTime * speeds->modelMoveSpeed);
                    break;
                case SelMode::FACE:
                case SelMode::VERT:
                    // TODO: 
                    // Add face and vertex moving
                    break;
                default:
                    break;
                }
                break;
        /* ========== Handle scaling ================= */
            case Tool::SCALE:
                switch (sel->GetSelMode()) {
                case SelMode::MESH:
                    mesh->SetScale(mesh->GetScale() + inputVec * speeds->modelScaleRate * deltaTime * mesh->GetScale());
                    break;
                case SelMode::FACE:
                case SelMode::VERT:
                    // TODO: 
                    // Add face and vertex moving
                    break;
                default:
                    break;
                }
                break;
        /* ========== Handle rotating ================ */
            case Tool::ROTATE:
                switch (sel->GetSelMode()) {
                case SelMode::MESH:
                    mesh->Rotate(glm::vec3(inputVec.y, inputVec.x, inputVec.z) * speeds->modelTurnSpeed * deltaTime);
                    break;
                case SelMode::FACE:
                case SelMode::VERT:
                    // TODO: 
                    // Add face and vertex moving
                    break;
                default:
                    break;
                }
                break;
        /* ========== Handle defaults ================ */
            case Tool::SELECT:
            case Tool::NONE:
            default:
                break;
            }
        }
        didReceiveInput = true;
    }

    /* =================================== Handle camera ================================== */
    if (ARROW_PRESS && !CTRL_PRESS && ALT_PRESS) {
        // Rotate camera
        camera->rotation += GetArrow(window) * speeds->cameraTurnSpeed * deltaTime;
        didReceiveInput = true;
    }

    /* =================================== Handle tools ================================== */
    /* ========== Handle saving ============== */
    if (S_PRESS && CTRL_PRESS) {
        if (!locks->lockCtrlS) {
            WriteObjToFile(scene, "../models/", mesh->GetName());
            locks->lockCtrlS = true;
        }
        didReceiveInput = true;
    }
    /* ========== Handle triangulation ============== */
    if (T_PRESS && CTRL_PRESS) {
        if (!locks->lockCtrlT) {
            // TODO:
            // Handle triangulation
            locks->lockCtrlT = true;
        }
        didReceiveInput = true;
    }
    /* ========== Handle rendering ============== */
    if (R_PRESS && CTRL_PRESS) {
        if (!locks->lockCtrlR) {
            // TODO:
            // Handle render
            locks->lockCtrlR = true;
        }
        didReceiveInput = true;
    }
    /* ========== Handle deletion ============== */
    if (DELETE_PRESS && !CTRL_PRESS) {
        if (!locks->lockDel) {
            // TODO:
            // Handle deletion
            locks->lockDel = true;
        }
        didReceiveInput = true;
    }

    /*
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
        if (CTRL_PRESS) {
            if (!locks->lockCtrlS) {
                WriteObjToFile(scene, "../models/", mesh->GetName());
                locks->lockCtrlS = true;
            }
        }
        // Move camera if alt is pressed
        else if (ALT_PRESS)
            camera->pos -= camera->dir * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(-mesh->GetForward() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        // Move camera if alt is pressed
        if (ALT_PRESS)
            camera->pos += camera->right * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(mesh->GetRight() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // Move camera if alt is pressed
        if (ALT_PRESS)
            camera->pos -= camera->right * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(-mesh->GetRight() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        // Move camera if alt is pressed
        if (ALT_PRESS)
            camera->pos += camera->up * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(mesh->GetUp() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }
    // Move down
    if (SHIFT_PRESS) {
        // Move camera if alt is pressed
        if (ALT_PRESS)
            camera->pos -= camera->up * deltaTime * speeds->cameraMoveSpeed;
        // Otherwise move model
        else
            mesh->Translate(-mesh->GetUp() * deltaTime * speeds->modelMoveSpeed);
        didReceiveInput = true;
    }

    // Scale up
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mesh->SetScale(mesh->GetScale() + glm::vec3(speeds->modelScaleRate * deltaTime) * mesh->GetScale());
        didReceiveInput = true;
    }
    // Scale down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        // Extrude on Ctrl+E
        if (CTRL_PRESS) {
            locks->rerender = true;
        }
        else {
            mesh->SetScale(mesh->GetScale() - glm::vec3(speeds->modelScaleRate * deltaTime) * mesh->GetScale());
        }
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
    */


    /* ==================================================== Mouse Input ===================================================== */
    // Mouse input
    if (MOUSE_PRESS) {
        // Handle moving with mouse
        if (ALT_PRESS) {
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
            if (LEFT_MOUSE_PRESS) {
                // Apply changes to camera
                camera->rotation.x += speeds->mouseTurnSpeed * deltaTime * deltaX;
                camera->rotation.y += speeds->mouseTurnSpeed * deltaTime * deltaY;
            }
            // Alt + RMB to move
            else if (RIGHT_MOUSE_PRESS) {
                // Apply changes to camera
                camera->pos += camera->right * speeds->mouseMoveSpeed * deltaTime * deltaX;
                camera->pos += camera->up * speeds->mouseMoveSpeed * deltaTime * deltaY;
            }

            // Keep mouse where it was clicked
            glfwSetCursorPos(window, (float)(*prevX), (float)(*prevY));
            didReceiveInput = true;
        }
        // Handle addition to selection
        else if (LEFT_MOUSE_PRESS && SHIFT_PRESS) {
            // If mouse is over the object, add it to selection
            //sel->SelectFace(<faceIndex>);
            //sel->SelectVert(<vertIndex>);
            // If the selected face or vert was already selected, deselect it
            //sel->DeselectFace(<faceIndex>);
            //sel->DeselectVert(<vertIndex>);
        }
        // Handle single selection/deselection
        else if (LEFT_MOUSE_PRESS) {
            // If mouse is over the object, replace the selection with it
            //sel->ClearSelection();
            //sel->SelectFace(<faceIndex>);
            //sel->SelectVert(<vertIndex>);
            // If the selected face or vert was already selected, deselect it
            //sel->DeselectFace(<faceIndex>);
            //sel->DeselectVert(<vertIndex>);
        }
    }
    // Reset previous click location when there 
    else {
        *prevX = -1;
        *prevY = -1;
    }
    


    /* ==================================================== Process Input ===================================================== */
    // Recalculate camera basis if any input was received
    if (didReceiveInput) {
        camera->CalcBasis();
        mesh->CalcBasis();
    }
    // If no input was received, clear all input locks
    else {
        locks->ClearLocks();
    }

    return didReceiveInput;
}

// Returns the combined input vector of arrow keys
glm::vec3 GetArrow(GLFWwindow* window)
{
    glm::vec3 output = glm::vec3(0, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        output += glm::vec3(0, 1, 0);
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        output += glm::vec3(0, -1, 0);
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        output += glm::vec3(-1, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        output += glm::vec3(1, 0, 0);

    return output;
}

// Returns the combined input vector of WASDZX
glm::vec3 GetWASDZX(GLFWwindow* window)
{
    glm::vec3 output = glm::vec3(0, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        output += glm::vec3(1, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        output += glm::vec3(-1, 0, 0);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        output += glm::vec3(0, 1, 0);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        output += glm::vec3(0, -1, 0);
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        output += glm::vec3(0, 0, 1);
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        output += glm::vec3(0, 0, -1);

    return output;
}

// Locks only the selected tool, releasing locks on other tools
void InputLocks::LockTool(Tool _tool)
{
    lockQ = (_tool == Tool::SELECT);
    lockE = (_tool == Tool::SCALE);
    lockR = (_tool == Tool::ROTATE);
    lockT = (_tool == Tool::MOVE);
    lockCtrlE = (_tool == Tool::EXTRUDE);
}

// Resets all locks on keys
void InputLocks::ClearLocks() {
    // Don't unlock tool selections
    //lockQ = false;			// Select
    //lockE = false;			// Scale
    //lockR = false;			// Rotate
    //lockT = false;			// Translate
    //lockCtrlE = false;		// Extrude

    lockF = false;
    lockCtrlR = false;		// Render
    lockCtrlT = false;		// Triangulate
    lockCtrlS = false;		// Save
    lockDel = false;        // Delete

    rerender = false;
}