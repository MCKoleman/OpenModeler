#pragma once
#include "triangle.h"
#include <unordered_map>

struct ITriangle {
	glm::vec3 normal;
	std::string mat;
	Vertex vertices[TRI_VERTS];
	int shadingGroup = -1;

	void SetMat(std::string _mat);
	void CalcNormal();

	ITriangle();
	ITriangle(Vertex i0, Vertex i1, Vertex i2, std::string _mat = "default", int _sg = -1);
	ITriangle(Triangle _tri, std::unordered_map<int, Vertex>& _verts);
};