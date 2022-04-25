#include "selection.h"

// Returns the entire selection as a selection of vertices
void Selection::GetSelectedVerts(std::vector<int>& _verts, Mesh* mesh)
{
	// Add all faces to selection
	for (auto iter = selFaces.begin(); iter != selFaces.end(); ++iter) {
		Face tempFace = mesh->GetFace(*iter);
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
void Selection::SelectFace(int _id)
{
	selFaces.emplace(_id);
}

// Selects the vertex with the given ID
void Selection::SelectVert(int _id)
{
	selVerts.emplace(_id);
}

// Deselects the face with the given ID
void Selection::DeselectFace(int _id)
{
	selFaces.erase(_id);
}

// Deselects the vertex with the given ID
void Selection::DeselectVert(int _id)
{
	selVerts.erase(_id);
}

// Clears the entire selection
void Selection::ClearSelection()
{
	selVerts.clear();
	selFaces.clear();
}

// Sets the tool selection
void Selection::SetTool(Tool _sel)
{
	tool = _sel;
}

// Returns the tool selection
Tool Selection::GetTool()
{
	return tool;
}

// Storage container for information on all selections
Selection::Selection()
{
	tool = Tool::NONE;
}