#pragma once
#include "glIncludes.h"
#include "mesh.h"
#include <set>

enum class Tool { NONE = 0, SELECT = 1, MOVE = 2, ROTATE = 3, SCALE = 4, EXTRUDE = 5 };
enum class SelMode { MESH = 0, VERT = 1, FACE = 2 };

struct Selection {
private:
	glm::vec3 pivot;
	std::set<int> selVerts;
	std::set<int> selFaces;
	Mesh* selMesh;

	Tool tool;
	SelMode selMode;
public:
	// Returns the entire selection as a selection of vertices
	void GetSelectedVerts(std::vector<int>& _verts);
	// Returns the entire selection as a selection of vertices
	void GetSelectedVerts(std::set<int>& _verts);

	// Selects the face with the given ID
	void SelectFace(int _id);
	// Selects the vertex with the given ID
	void SelectVert(int _id);
	// Selects the given mesh
	void SelectMesh(Mesh* mesh);
	// Deselects the face with the given ID
	void DeselectFace(int _id);
	// Deselects the vertex with the given ID
	void DeselectVert(int _id);
	// Deselects the currently selected mesh
	void DeselectMesh();

	// Clears the vertex selection
	void ClearVertSel();
	// Clears the face selection
	void ClearFaceSel();
	// Clears the entire selection
	void ClearSelection();
	// Sets the selection pivot
	void SetSelectionPivot(glm::vec3 _pivot);
	// Calculates the selection pivot
	void CalcSelPivot();
	// Sets the tool selection
	void SetTool(Tool _sel);
	// Sets the selection mode
	void SetSelMode(SelMode _sel);
	// Returns the tool selection
	Tool GetTool();
	// Returns the selection mode
	SelMode GetSelMode();
	// Returns the selected mesh
	Mesh* GetSelectedMesh();

	// Storage container for information on all selections
	Selection();
};