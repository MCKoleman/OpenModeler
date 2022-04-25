#pragma once
#include "glIncludes.h"
#include "scene.h"
#include "indexStructs.h"
#include "ray.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class RayTracer
{
public:
	Ray generateRay(Camera* camera, float u, float v);
	glm::vec3 bisector(glm::vec3 a, glm::vec3 b);
	glm::vec3 normal(std::vector<glm::vec3>& vPos);
	glm::vec3 getPixelColor(Scene* scene, Ray& r, int count);
	glm::vec3* RayTrace(Scene* scene);
};