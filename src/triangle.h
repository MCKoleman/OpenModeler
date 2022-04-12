#pragma once
#include "vertex.h"
#include "material.h"

const unsigned int TRI_VERTS = 3;

struct Triangle {
	Material mat;
	int vertices[TRI_VERTS];
	int shadingGroup = -1;

	void SetMat(Material _mat);
	glm::vec3 CalcNormal();

	Triangle();
	Triangle(int i0, int i1, int i2);
	Triangle(int i0, int i1, int i2, Material _mat);
	Triangle(int i0, int i1, int i2, Material _mat, int _sg);
};