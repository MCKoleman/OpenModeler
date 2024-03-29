#include "selection.h"
#include "rayTracer.h"
#include "scene.h"
#include "openHelper.h"
#include "indexStructs.h"
#include <iostream>

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

// Returns the entire selection as a selection of vertices
void Selection::GetSelectedVerts(std::set<int>& _verts)
{
	// Add all faces to selection
	for (auto iter = selFaces.begin(); iter != selFaces.end(); ++iter) {
		Face tempFace = selMesh->GetFace(*iter);
		for (int i = 0; i < tempFace.GetNumVerts(); i++) {
			_verts.emplace(tempFace.vertices[i]);
		}
	}

	// Add all verts to selection
	for (auto iter = selVerts.begin(); iter != selVerts.end(); ++iter) {
		_verts.emplace(*iter);
	}
}

// Selects the face with the given ID
void Selection::SelectFace(int _id, bool _deselect) 
{
	if (_id < 0)
		return;
	if (_deselect)
		selFaces.clear();

	selFaces.emplace(_id); 
	std::cout << "Selected face [" << _id << "].\n"; 
}

// Selects the vertex with the given ID
void Selection::SelectVert(int _id, bool _deselect) 
{ 
	if (_id < 0)
		return;
	if (_deselect)
		selVerts.clear();

	selVerts.emplace(_id); 
	std::cout << "Selected vertex [" << _id << "].\n"; 
}

// Selects the given mesh
void Selection::SelectMesh(Mesh* mesh) 
{
	if (mesh == nullptr)
		return;

	selMesh = mesh; 
	std::cout << "Selected mesh [" << selMesh << "].\n"; 
}

// Deselects the face with the given ID
void Selection::DeselectFace(int _id) 
{ 
	selFaces.erase(_id); 
	std::cout << "Deselected face [" << _id << "].\n"; 
}

// Deselects the vertex with the given ID
void Selection::DeselectVert(int _id) 
{ 
	selVerts.erase(_id); 
	std::cout << "Deselected vertex [" << _id << "].\n"; 
}

// Deselects the currently selected mesh
void Selection::DeselectMesh() 
{
	if (selMesh == nullptr)
		return;

	selMesh = nullptr; 
	std::cout << "Deselected mesh.\n"; 
}

// Clears the vertex selection
void Selection::ClearVertSel() { selVerts.clear(); }
// Clears the face selection
void Selection::ClearFaceSel() { selFaces.clear(); }
// Clears the entire selection
void Selection::ClearSelection() { ClearFaceSel(); ClearVertSel(); }

// Sets the selection pivot
void Selection::SetSelectionPivot(glm::vec3 _pivot) { pivot = _pivot; }
// Returns the selection pivot
glm::vec3 Selection::GetSelectionPivot() { return pivot; }

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
	switch (selMode) {
	case SelMode::MESH:
		std::cout << "Selected mode [MESH]\n";
		break;
	case SelMode::FACE:
		std::cout << "Selected mode [FACE]\n";
		break;
	case SelMode::VERT:
		std::cout << "Selected mode [VERT]\n";
		break;
	}
}

// Returns whether the given vertex is selected
bool Selection::IsVertSelected(int _id) { return selVerts.find(_id) != selVerts.end(); }
// Returns whether the given face is selected
bool Selection::IsFaceSelected(int _id) { return selFaces.find(_id) != selFaces.end(); }

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

// Returns the nearest mesh to the clicked position
Mesh* Selection::GetNearestMesh(Scene* scene, int i, int j)
{
	//std::cout << "Clicked [" << i << ", " << j << "]\n";
	float u = (j + 0.5f) / SCR_WIDTH;
	float v = (i + 0.5f) / SCR_HEIGHT;
	//std::cout << "Transformed click [" << u << ", " << v << "]\n";
	Ray ray = RayTracer::generateRay(scene, u, v, false);
	if (ray.DoesIntersect(scene->GetRenderTris()))
		return scene->GetMeshes()->GetAll().begin()->second;
	else
		return nullptr;
}

// Returns the nearest vertex to the clicked position
int Selection::GetNearestVert(Scene* scene, int i, int j)
{
	float u = (j + 0.5f) / SCR_WIDTH;
	float v = (i + 0.5f) / SCR_HEIGHT;
	Ray ray = RayTracer::generateRay(scene, u, v, false);
	IndVertex res = ray.GetClosestVertex(scene->GetRenderTris());
	return res.id;
}

// Returns the nearest face to the clicked position
int Selection::GetNearestFace(Scene* scene, int i, int j)
{
	float u = (j + 0.5f) / SCR_WIDTH;
	float v = (i + 0.5f) / SCR_HEIGHT;
	Ray ray = RayTracer::generateRay(scene, u, v, false);
	ITriangle res = ray.GetClosestTriangle(scene->GetRenderTris());
	return res.triIndex;
}