#pragma once
#include "vertex.h"
#include "material.h"
#include "indexStructs.h"
#include <vector>
#include <unordered_map>

struct Triangle;
struct Face {
	std::string mat;
	std::vector<int> vertices;
	int shadingGroup = -1;
	
	void GetTri(std::vector<Triangle>& tris, std::unordered_map<int, Vertex>& tempVerts);
	int GetNumVerts();
	int GetVertex(int _index);
	void SetVertex(int _vertex, int _index);
	void SetVertices(std::vector<int>& _verts);

	void SetMat(std::string _mat);
	glm::vec3 CalcNormal(std::vector<int>& _verts);
	void Clear();

	Face(std::string _mat = "default", int _sg = -1);
	Face(int i0, int i1, int i2, std::string _mat = "default", int _sg = -1);
	Face(int i0, int i1, int i2, int i3, std::string _mat = "default", int _sg = -1);
	Face(std::vector<int>& _verts, std::string _mat = "default", int _sg = -1);
	Face(std::vector<IndVertex>& _verts, std::string _mat = "default", int _sg = -1);
	~Face();
};