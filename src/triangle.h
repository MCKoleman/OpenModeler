#pragma once
#include "vertex.h"
#include "material.h"

const unsigned int TRI_VERTS = 3;

struct Triangle {
	Material mat;
	int shadingGroup = -1;

	void SetMat(Material _mat);
	virtual glm::vec3 CalcNormal() = 0;

	Triangle();
};

struct STriangle : public Triangle {
	Vertex vertices[TRI_VERTS];
	glm::vec3 CalcNormal();

	STriangle();
	STriangle(Vertex v0, Vertex v1, Vertex v2);
	STriangle(Vertex v0, Vertex v1, Vertex v2, Material _mat);
	STriangle(Vertex v0, Vertex v1, Vertex v2, Material _mat, int _sg);
};

struct ITriangle : public Triangle {
	int vertices[TRI_VERTS];
	glm::vec3 CalcNormal();

	ITriangle();
	ITriangle(int i0, int i1, int i2);
	ITriangle(int i0, int i1, int i2, Material _mat);
	ITriangle(int i0, int i1, int i2, Material _mat, int _sg);
};