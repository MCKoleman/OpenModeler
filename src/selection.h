#pragma once
#include "glIncludes.h"
#include "mesh.h"
#include <set>

enum class Tool { NONE = 0, MOVE = 1, ROTATE = 2, SCALE = 3, EXTRUDE = 4 };

struct Selection {
private:
	std::set<int> selVerts;
	std::set<int> selFaces;
	Tool tool;
public:
	// Returns the entire selection as a selection of vertices
	void GetSelectedVerts(std::vector<int>& _verts, Mesh* mesh);

	// Selects the face with the given ID
	void SelectFace(int _id);
	// Selects the vertex with the given ID
	void SelectVert(int _id);
	// Deselects the face with the given ID
	void DeselectFace(int _id);
	// Deselects the vertex with the given ID
	void DeselectVert(int _id);

	// Clears the entire selection
	void ClearSelection();
	// Sets the tool selection
	void SetTool(Tool _sel);
	// Returns the tool selection
	Tool GetTool();

	// Storage container for information on all selections
	Selection();
};