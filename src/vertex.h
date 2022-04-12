#pragma once
#include "glIncludes.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 texture;

	Vertex();
	Vertex(glm::vec3 _pos, glm::vec3 _normal);
	Vertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec3 _text);
};