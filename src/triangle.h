#pragma once
#include "vertex.h"
#include "material.h"

const unsigned int TRI_VERTS = 3;

struct Face;
struct Triangle {
	std::string mat;
	int vertices[TRI_VERTS];
	int shadingGroup = -1;

	Face GetFace();
	void SetMat(std::string _mat);
	glm::vec3 CalcNormal();

	Triangle();
	Triangle(int i0, int i1, int i2);
	Triangle(int i0, int i1, int i2, std::string _mat);
	Triangle(int i0, int i1, int i2, std::string _mat, int _sg);
};

bool IsClockwise(glm::vec3 a, glm::vec3 b, glm::vec3 c);