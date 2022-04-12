#pragma once
#include "fileHelper.h"
#include "mesh.h"
#include "camera.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// OpenGL helper functions
GLFWwindow* OpenGLInitWindow(int width, int height, std::string name);

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
glm::mat4 CalcMVP(Camera* camera, Mesh* mesh);
glm::mat4 GetProjectionMatrix(Camera* camera);
glm::mat4 GetViewMatrix(Camera* camera);
glm::mat4 GetModelMatrix(Mesh* mesh);