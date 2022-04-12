#pragma once
#include "glIncludes.h"
#include "camera.h"
#include "mesh.h"
#include "options.h"

#define SHIFT_PRESS (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
#define ALT_PRESS (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
#define CTRL_PRESS (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
#define MOUSE_PRESS (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)

bool ProcessInput(GLFWwindow* window, Camera* camera, Mesh* mesh, float deltaTime, SpeedConsts* speeds, int* prevX, int* prevY);