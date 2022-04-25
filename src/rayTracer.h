#pragma once
#include "glIncludes.h"
#include "scene.h"
#include "indexStructs.h"
#include "ray.h"

class RayTracer
{
public:
	static Ray generateRay(Camera* camera, float u, float v);
	static glm::vec3 bisector(glm::vec3 a, glm::vec3 b);
	static glm::vec3 normal(std::vector<glm::vec3>& vPos);
	static glm::vec3 getPixelColor(Scene* scene, Ray& r, int count);
	static void RayTrace(Scene* scene, std::vector<glm::vec4>& result);
};