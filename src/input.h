#pragma once
#include "scene.h"
#include "options.h"
#include "objWriter.h"
#include "selection.h"

#define SHIFT_PRESS (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
#define ALT_PRESS (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
#define CTRL_PRESS (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
#define MOUSE_PRESS (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
#define LEFT_MOUSE_PRESS (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
#define RIGHT_MOUSE_PRESS (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)

// Input lock structure to separate presses from holding keyes
struct InputLocks {
	bool lockCtrlS = false;

	void ClearLocks();
};

bool ProcessInput(GLFWwindow* window, Scene* scene, Selection* sel, InputLocks* locks, float deltaTime, SpeedConsts* speeds, int* prevX, int* prevY);