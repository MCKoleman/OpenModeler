#pragma once
#include "vertex.h"
#include "material.h"

const unsigned int TRI_VERTS = 3;

struct Triangle {
	std::string mat;
	int vertices[TRI_VERTS];
	int shadingGroup = -1;

	void SetMat(std::string _mat);
	glm::vec3 CalcNormal();

	Triangle();
	Triangle(int i0, int i1, int i2);
	Triangle(int i0, int i1, int i2, std::string _mat);
	Triangle(int i0, int i1, int i2, std::string _mat, int _sg);
};