#include "triangle.h"
#include "face.h"

void Triangle::SetMat(std::string _mat)
{
	mat = _mat;
}

// Converts the triangle into a face
Face Triangle::GetFace()
{
	return Face(vertices[0], vertices[1], vertices[2], mat, shadingGroup);
}

Triangle::Triangle() : Triangle(-1, -1, -1, "", -1) {}
Triangle::Triangle(int i0, int i1, int i2) : Triangle(i0, i1, i2, "", -1) {}
Triangle::Triangle(int i0, int i1, int i2, std::string _mat) : Triangle(i0, i1, i2, _mat, -1) {}
Triangle::Triangle(int i0, int i1, int i2, std::string _mat, int _sg)
{
	normal = glm::vec3();
	vertices[0] = i0;
	vertices[1] = i1;
	vertices[2] = i2;
	mat = _mat;
	shadingGroup = _sg;
}

Triangle::Triangle(int i0, int i1, int i2, glm::vec3 _norm, glm::vec3 _center, std::string _mat, int _sg, int _triIndex, TriTag _tag)
{
	triIndex = _triIndex;
	tag = _tag;
	normal = _norm;
	center = _center;
	vertices[0] = i0;
	vertices[1] = i1;
	vertices[2] = i2;
	mat = _mat;
	shadingGroup = _sg;
}

glm::vec3 Triangle::CalcNormal()
{
	return glm::vec3();
	//glm::vec3 u = vertices[1].pos - vertices[0].pos;
	//glm::vec3 v = vertices[2].pos - vertices[0].pos;
	//return glm::vec3((u.y * v.z - u.z * v.y), (u.z * v.x - u.x * v.z), (u.x * v.y - u.y * v.x));
}