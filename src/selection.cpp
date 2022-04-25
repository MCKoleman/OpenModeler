#include "selection.h"

// Returns the entire selection as a selection of vertices
void Selection::GetSelectedVerts(std::vector<int>& _verts)
{
	// Add all faces to selection
	for (auto iter = selFaces.begin(); iter != selFaces.end(); ++iter) {
		Face tempFace = selMesh->GetFace(*iter);
		for (int i = 0; i < tempFace.GetNumVerts(); i++) {
			_verts.push_back(tempFace.vertices[i]);
		}
	}

	// Add all verts to selection
	for (auto iter = selVerts.begin(); iter != selVerts.end(); ++iter) {
		_verts.push_back(*iter);
	}
}

// Selects the face with the given ID
void Selection::SelectFace(int _id) { selFaces.emplace(_id); }
// Selects the vertex with the given ID
void Selection::SelectVert(int _id) { selVerts.emplace(_id); }
// Selects the given mesh
void Selection::SelectMesh(Mesh* mesh) { selMesh = mesh; }
// Deselects the face with the given ID
void Selection::DeselectFace(int _id) { selFaces.erase(_id); }
// Deselects the vertex with the given ID
void Selection::DeselectVert(int _id) { selVerts.erase(_id); }
// Deselects the currently selected mesh
void Selection::DeselectMesh() { selMesh = nullptr; }

// Clears the vertex selection
void Selection::ClearVertSel() { selVerts.clear(); }
// Clears the face selection
void Selection::ClearFaceSel() { selFaces.clear(); }
// Clears the entire selection
void Selection::ClearSelection() { ClearFaceSel(); ClearVertSel(); }

// Sets the selection pivot
void Selection::SetSelectionPivot(glm::vec3 _pivot) { pivot = _pivot; }

// Calculates the selection pivot
void Selection::CalcSelPivot()
{
	// Reset pivot if nothing is selected
	if (selMesh == nullptr)
		pivot = glm::vec3(0, 0, 0);
	// Use mesh pivot as center
	else if (selVerts.size() == 0 && selFaces.size() == 0)
		pivot = selMesh->GetPivot();
	// Calculate center for face selection
	else if (selFaces.size() != 0) {
		pivot = glm::vec3(0, 0, 0);
		for (auto iter = selFaces.begin(); iter != selFaces.end(); ++iter) {
			pivot += selMesh->GetFace(*iter).center;
		}
		pivot /= (float)selFaces.size();
	}
	// Calculate center for vertex selection
	else if (selVerts.size() != 0) {
		pivot = glm::vec3(0, 0, 0);
		for (auto iter = selVerts.begin(); iter != selVerts.end(); ++iter) {
			pivot += selMesh->GetVert(*iter).pos;
		}
		pivot /= (float)selVerts.size();
	}
}

#include <iostream>
// Sets the tool selection
void Selection::SetTool(Tool _sel)
{
	tool = _sel;
	switch (tool) {
	case Tool::NONE:
		std::cout << "Selected tool [NONE]\n";
		break;
	case Tool::MOVE:
		std::cout << "Selected tool [MOVE]\n";
		break;
	case Tool::SCALE:
		std::cout << "Selected tool [SCALE]\n";
		break;
	case Tool::ROTATE:
		std::cout << "Selected tool [ROTATE]\n";
		break;
	case Tool::EXTRUDE:
		std::cout << "Selected tool [EXTRUDE]\n";
		break;
	case Tool::SELECT:
		std::cout << "Selected tool [SELECT]\n";
		break;
	}
}
// Sets the selection mode
void Selection::SetSelMode(SelMode _sel)
{
	selMode = _sel;
}

// Returns the tool selection
Tool Selection::GetTool() { return tool; }
// Returns the selection mode
SelMode Selection::GetSelMode() { return selMode; }
// Returns the selected mesh
Mesh* Selection::GetSelectedMesh() { return selMesh; }

// Storage container for information on all selections
Selection::Selection()
{
	tool = Tool::NONE;
	selMode = SelMode::MESH;
	pivot = glm::vec3(0, 0, 0);
	selMesh = nullptr;
}