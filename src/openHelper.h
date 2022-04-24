#pragma once
#include "fileHelper.h"
#include "indexStructs.h"
#include "scene.h"
#include "selection.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// OpenGL helper functions
GLFWwindow* OpenGLInitWindow(int width, int height, std::string name);
void OpenGLInitBuffers(ProgramIDs* ids, int vertsSize, float* vertices, int indicesSize, unsigned int* indices);
void OpenGLDraw(Scene* scene, Selection* sel, ProgramIDs* ids, int indicesSize, unsigned int* indices);
void OpenGLCleanup(ProgramIDs* ids);

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
glm::mat4 CalcMVP(Scene* scene);
glm::mat4 GetProjectionMatrix(Scene* scene);
glm::mat4 GetViewMatrix(Scene* scene);
glm::mat4 GetModelMatrix(Scene* scene);