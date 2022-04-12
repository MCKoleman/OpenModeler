#pragma once
#include "mesh.h"
#include "meshModel.h"
#include "glIncludes.h"

// An indexed vertex. Used to facilitate indexed triangle structures
struct IndVertex {
	Vertex ver;
	int id;

	IndVertex() : id(-1), ver(Vertex()) {}
	IndVertex(int _id) : id(_id), ver(Vertex()) {}
	IndVertex(int _id, Vertex _ver) : id(_id), ver(_ver) {}
};

// Data needed for constructing a face
struct FaceData {
	std::vector<IndVertex> vertexInfo;
	std::string matName;
	int shadingGroup;
	int id;

	FaceData() : matName(""), shadingGroup(-1), id(-1) {}
	FaceData(std::vector<IndVertex>& _verts) : matName(""), vertexInfo(_verts), shadingGroup(-1), id(-1) {}
	FaceData(std::vector<IndVertex>& _verts, std::string _mat) : matName(_mat), vertexInfo(_verts), shadingGroup(-1), id(-1) {}
	FaceData(std::vector<IndVertex>& _verts, std::string _mat, int _sg) : matName(_mat), vertexInfo(_verts), shadingGroup(_sg), id(-1) {}
	FaceData(std::vector<IndVertex>& _verts, std::string _mat, int _sg, int _id) : matName(_mat), vertexInfo(_verts), shadingGroup(_sg), id(_id) {}
};

// A string and an int. A strint, if you will
struct Strint {
	std::string str;
	int id;

	Strint() : id(-1), str("") {}
	Strint(int _id) : id(_id), str("") {}
	Strint(int _id, std::string _str) : id(_id), str(_str) {}
};

// An indexed vector. Used for storing data needed to build a vertex
struct IndVec3 {
	glm::vec3 pos;
	int id;

	IndVec3() : id(-1), pos(glm::vec3()) {}
	IndVec3(int _id) : id(_id), pos(glm::vec3()) {}
	IndVec3(int _id, glm::vec3 _pos) : id(_id), pos(_pos) {}
};

int FindVertIndex(std::vector<IndVertex>& verts, int id);
int FindVertIndex(std::vector<IndVec3>& verts, int id);
int FindFaceIndex(std::vector<FaceData>& faces, int id);
IndVertex FindVert(std::vector<IndVertex>& verts, int id);
IndVec3 FindVert(std::vector<IndVec3>& verts, int id);
FaceData FindFace(std::vector<FaceData>& faces, int id);