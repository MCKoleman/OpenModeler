#pragma once
#include "glIncludes.h"
#include "scene.h"
#include "indexStructs.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;
	Ray(glm::vec3 origin, glm::vec3 direction);
};

class RayTracer
{
public:
	Ray generateRay(Camera* camera, float u, float v);
	glm::vec3 bisector(glm::vec3 a, glm::vec3 b);
	glm::vec3 normal(std::vector<glm::vec3>& vPos);
	float get_t(std::vector<glm::vec3>& vPos, Ray& r);
	bool intersectTriangle(std::vector<glm::vec3>& vPos, Ray& r);
	Strint getClosestTriangle(std::unordered_map<std::string, Mesh*>& meshes, Ray& r);
	glm::vec3 getPixelColor(Scene* scene, Ray& r, int count);
	glm::vec3* RayTrace(Scene* scene);
};