#include "triangle.h"

void Triangle::SetMat(Material _mat)
{
	mat = _mat;
}

Triangle::Triangle() : Triangle(-1, -1, -1, Material(), -1) {}
Triangle::Triangle(int i0, int i1, int i2) : Triangle(i0, i1, i2, Material(), -1) {}
Triangle::Triangle(int i0, int i1, int i2, Material _mat) : Triangle(i0, i1, i2, _mat, -1) {}
Triangle::Triangle(int i0, int i1, int i2, Material _mat, int _sg)
{
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