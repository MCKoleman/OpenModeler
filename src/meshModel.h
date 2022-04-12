#pragma once
#include "mesh.h"

class SMesh : public Mesh {
protected:
	std::vector<STriangle> tris;
public:
	// Adds the given tri to this mesh
	void AddTri(STriangle _tri);

	// Sets the tri at the given index to the given tri
	void SetTri(size_t index, STriangle _tri);

	// Returns the tri at the given index
	STriangle GetTri(size_t index);

	// Returns the size of the mesh if it was converted into a vertex array (needed for allocating memory for ConvertToVertData())
	int GetVertCount();

	// Gets the number of tris in the mesh
	int GetTriCount();

	// Converts this mesh into a vertex array and stores it in the given array
	void ConvertToVertData(float out[]);

	// Converts this mesh into a vertex array with vertex, color, and normal data
	void ConvertToVertColorNormalData(float out[]);

	// Clears the mesh of all tris
	void ClearTris();

	// Vertex model of the mesh [0 for separate, 1 for indexed]
	int GetVertexModel();

	// Recalculates the normals of the mesh
	void RecalculateNormals();

	~SMesh();
};

class IMesh : public Mesh {
protected:
	std::vector<ITriangle> tris;
	std::unordered_map<int, Vertex> verts;
public:
	int lastVertIndex = 0;

	// Adds the given tri to this mesh
	void AddTri(ITriangle _tri);

	// Adds the given vert to this mesh. Returns the index that it was placed at
	int AddVert(Vertex _vert);
	int AddVert(int _index, Vertex _vert);

	// Sets the tri at the given index to the given tri
	void SetTri(size_t index, ITriangle _tri);

	// Returns the tri at the given index
	ITriangle GetTri(size_t index);

	// Returns the number of verts in this mesh if it was converted into a vertex array (needed for allocating memory for ConvertToVertData())
	int GetVertCount();

	// Returns the number of indexes in this mesh
	int GetIndexCount();

	// Gets the number of tris in the mesh
	int GetTriCount();

	// Converts this mesh into a vertex array and stores it in the given array
	void ConvertToVertData(float out[]);

	// Converts this mesh into a index array and stores it in the given array
	void ConvertToIndexData(unsigned int out[]);

	// Clears the mesh of all tris
	void ClearTris();

	// Vertex model of the mesh [0 for separate, 1 for indexed]
	int GetVertexModel();

	// Recalculates the normals of the mesh
	void RecalculateNormals();

	~IMesh();
};