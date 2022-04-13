#include "mesh.h"

void Mesh::CalcBasis()
{
    forward = glm::vec3(
        cos(rotation.y) * sin(rotation.x),
        sin(rotation.y),
        cos(rotation.y) * cos(rotation.x)
    );

    // Right vector
    right = glm::vec3(
        sin(rotation.x - HALF_PI),
        0,
        cos(rotation.x - HALF_PI)
    );

    // Up vector : perpendicular to both direction and right
    up = glm::cross(right, forward);
}

glm::vec3 Mesh::GetUp()
{
    return up;
}

glm::vec3 Mesh::GetRight()
{
    return right;
}

glm::vec3 Mesh::GetForward()
{
    return forward;
}

void Mesh::Translate(glm::vec3 _deltaPos)
{
    pos += _deltaPos;
}

void Mesh::Rotate(glm::vec3 _deltaRot)
{
    rotation += _deltaRot;
}

void Mesh::Scale(glm::vec3 _deltaScale)
{
    scale = glm::vec3(scale.x * _deltaScale.x, scale.y * _deltaScale.y, scale.z * _deltaScale.z);
}

glm::vec3 Mesh::GetPos()
{
    return pos;
}

glm::vec3 Mesh::GetRotation()
{
    return rotation;
}

glm::vec3 Mesh::GetScale()
{
    return scale;
}

void Mesh::SetPos(glm::vec3 _pos)
{
    pos = _pos;
}

void Mesh::SetRotation(glm::vec3 _rot)
{
    rotation = _rot;
}

void Mesh::SetScale(glm::vec3 _scale)
{
    scale = glm::max(_scale, MIN_SCALE);
}

// Mesh main function definitions
// ------------------------------
void Mesh::AddTri(Triangle _tri)
{
	tris.push_back(_tri);
}

int Mesh::AddVert(Vertex _vert)
{
	return AddVert(lastVertIndex + 1, _vert);
}

int Mesh::AddVert(int _index, Vertex _vert)
{
	// Only add the vertex if it doesn't exist in the mesh yet
	if (verts.find(_index) == verts.end()) {
		verts.emplace(_index, _vert);
		lastVertIndex = std::max(lastVertIndex, _index);
	}
	return _index;
}

void Mesh::SetTri(size_t index, Triangle _tri)
{
	tris[index] = _tri;
}

Triangle Mesh::GetTri(size_t index)
{
	return tris[index];
}

void Mesh::ClearTris()
{
	tris.clear();
	verts.clear();
	lastVertIndex = -1;
}

int Mesh::GetVertCount()
{
	return (int)verts.size();
}

int Mesh::GetIndexCount()
{

	return (int)tris.size() * 3;
}

int Mesh::GetTriCount()
{
	return (int)tris.size();
}

std::vector<Triangle>& Mesh::GetTris()
{
	return tris;
}

std::unordered_map<int, Vertex>& Mesh::GetVerts()
{
	return verts;
}

std::string Mesh::GetName() { return name; }
void Mesh::SetName(std::string _name) { name = _name; }

void Mesh::RecalculateNormals()
{
	// Reset normals for each tri
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			verts[tris[i].vertices[j]].normal = glm::vec3(0, 0, 0);
		}
	}

	// Calculate normals for each tri
	for (int i = 0; i < tris.size(); i++) {
		glm::vec3 triNorm = tris[i].CalcNormal();

		for (int j = 0; j < TRI_VERTS; j++) {
			verts[tris[i].vertices[j]].normal += triNorm;
		}
	}

	// Normalize normals for each vertex
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			verts[tris[i].vertices[j]].normal = glm::normalize(verts[tris[i].vertices[j]].normal);
		}
	}
}

int Mesh::GetVertexModel() { return 1; }

Mesh::Mesh()
{
    pos = glm::vec3();
}

Mesh::~Mesh()
{
	ClearTris();
}