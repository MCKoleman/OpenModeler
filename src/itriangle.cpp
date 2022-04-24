#include "itriangle.h"

void ITriangle::SetMat(std::string _mat)
{
	mat = _mat;
}

void ITriangle::CalcNormal()
{
	normal = glm::cross(vertices[1].pos - vertices[0].pos, vertices[2].pos - vertices[0].pos);
}

ITriangle::ITriangle()
{
	mat = "default";
	shadingGroup = -1;
	vertices[0] = Vertex();
	vertices[1] = Vertex();
	vertices[2] = Vertex();
	CalcNormal();
}

ITriangle::ITriangle(Vertex i0, Vertex i1, Vertex i2, std::string _mat, int _sg)
{
	mat = _mat;
	shadingGroup = _sg;
	vertices[0] = i0;
	vertices[1] = i1;
	vertices[2] = i2;
	CalcNormal();
}

ITriangle::ITriangle(Triangle _tri, std::unordered_map<int, Vertex>& _verts)
{
	mat = _tri.mat;
	shadingGroup = _tri.shadingGroup;
	vertices[0] = _verts[_tri.vertices[0]];
	vertices[1] = _verts[_tri.vertices[1]];
	vertices[2] = _verts[_tri.vertices[2]];
	CalcNormal();
}