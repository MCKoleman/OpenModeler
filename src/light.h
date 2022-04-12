#pragma once
#include "glIncludes.h"

struct Light {
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 color;
	float ka;
	float ks;

	Light();
	Light(glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _color, float _ka, float _ks);
};