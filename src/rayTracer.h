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
	float get_t(ITriangle& tri, Ray& r);
	bool intersectTriangle(ITriangle& tri, Ray& r);
	ITriangle* getClosestTriangle(std::vector<ITriangle>& tris, Ray& r);
	glm::vec3 getPixelColor(Scene* scene, Ray& r, int count);
	glm::vec3* RayTrace(Scene* scene);
};