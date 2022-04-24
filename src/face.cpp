#include "face.h"
#include "triangle.h"

// Adds the triangulated face to the given out parameter
void Face::GetTri(std::vector<Triangle>& tris, std::unordered_map<int, Vertex>& tempVerts)
{
	// Handle edge cases
	if (vertices.size() < 3) {
		return;
	}
	// Handle triangles
	else if (vertices.size() == 3) {
		// Is abc a clockwise face?
		if (IsClockwise(tempVerts[vertices[0]].pos, tempVerts[vertices[1]].pos, tempVerts[vertices[2]].pos)) {
			tris.push_back(Triangle(vertices[0], vertices[1], vertices[2], mat, shadingGroup));
		}
		// If abc is ccw, then acb should be clockwise
		else {
			tris.push_back(Triangle(vertices[0], vertices[2], vertices[1], mat, shadingGroup));
		}
	}
	// Handle quads
	else if (vertices.size() == 4) {
		float dist1 = glm::distance(tempVerts[vertices[0]].pos, tempVerts[vertices[2]].pos);
		float dist2 = glm::distance(tempVerts[vertices[1]].pos, tempVerts[vertices[3]].pos);
		if (dist1 > dist2) {
			tris.push_back(Triangle(vertices[0], vertices[1], vertices[3], mat, shadingGroup));
			tris.push_back(Triangle(vertices[1], vertices[2], vertices[3], mat, shadingGroup));
		}
		else {
			tris.push_back(Triangle(vertices[0], vertices[1], vertices[2], mat, shadingGroup));
			tris.push_back(Triangle(vertices[0], vertices[2], vertices[3], mat, shadingGroup));
		}
	}
	// Handle ngons
	else if (vertices.size() > 4) {
		for (int i = 0; i < vertices.size() - 2; i++) {
			if (i < vertices.size() - 3) {
				float dist1 = glm::distance(tempVerts[vertices[i]].pos, tempVerts[vertices[i + 2]].pos);
				float dist2 = glm::distance(tempVerts[vertices[i + 1]].pos, tempVerts[vertices[i + 3]].pos);

				if (dist1 > dist2) {
					tris.push_back(Triangle(vertices[i], vertices[i + 1], vertices[i + 3], mat, shadingGroup));
					tris.push_back(Triangle(vertices[i + 1], vertices[i + 2], vertices[i + 3], mat, shadingGroup));
				}
				else {
					tris.push_back(Triangle(vertices[i], vertices[i + 1], vertices[i + 2], mat, shadingGroup));
					tris.push_back(Triangle(vertices[i], vertices[i + 2], vertices[i + 3], mat, shadingGroup));
				}
				// If two tris were handled at once, skip the next one
				i++;
			}
			else {
				// Is abc a clockwise face?
				if (IsClockwise(tempVerts[vertices[i]].pos, tempVerts[vertices[i + 1]].pos, tempVerts[vertices[i + 2]].pos)) {
					tris.push_back(Triangle(vertices[i], vertices[i + 1], vertices[i + 2], mat, shadingGroup));
				}
				// If abc is ccw, then acb should be clockwise
				else {
					tris.push_back(Triangle(vertices[i], vertices[i + 2], vertices[i + 1], mat, shadingGroup));
				}
			}
		}
	}
}

int Face::GetNumVerts()
{
	return (int)vertices.size();
}

int Face::GetVertex(int _index)
{
	if (_index >= 0 && _index < vertices.size())
		return vertices[_index];
	else
		return -1;
}

void Face::SetVertex(int _vertex, int _index)
{
	// Do nothing for negative indices
	if (_index < 0)
		return;

	// Overwrite existing vertices
	if (_index > vertices.size()) {
		vertices[_index] = _vertex;
		return;
	}

	// If the vertex is past the end of the list, simply add it to the end
	vertices.push_back(_vertex);
}

void Face::SetVertices(std::vector<int>& _verts)
{
	Clear();
	for (int i = 0; i < _verts.size(); i++) {
		vertices.push_back(_verts[i]);
	}
}

void Face::SetMat(std::string _mat)
{
	mat = _mat;
}

glm::vec3 Face::CalcNormal(std::vector<int>& _verts)
{
	return glm::vec3();
}

void Face::Clear()
{
	vertices.clear();
}

Face::Face(std::string _mat, int _sg)
{
	mat = _mat;
	shadingGroup = _sg;
}

Face::Face(int i0, int i1, int i2, std::string _mat, int _sg)
{
	mat = _mat;
	shadingGroup = _sg;
	vertices.push_back(i0);
	vertices.push_back(i1);
	vertices.push_back(i2);
}

Face::Face(int i0, int i1, int i2, int i3, std::string _mat, int _sg)
{
	mat = _mat;
	shadingGroup = _sg;
	vertices.push_back(i0);
	vertices.push_back(i1);
	vertices.push_back(i2);
	vertices.push_back(i3);
}

Face::Face(std::vector<int>& _verts, std::string _mat, int _sg)
{
	mat = _mat;
	shadingGroup = _sg;
	for (int i = 0; i < _verts.size(); i++) {
		vertices.push_back(_verts[i]);
	}
}

Face::Face(std::vector<IndVertex>& _verts, std::string _mat, int _sg)
{
	mat = _mat;
	shadingGroup = _sg;
	for (int i = 0; i < _verts.size(); i++) {
		vertices.push_back(_verts[i].id);
	}
}

Face::~Face()
{
	Clear();
}