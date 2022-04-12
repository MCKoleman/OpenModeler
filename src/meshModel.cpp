#include "meshModel.h"

// SMesh definitions
// -----------------
void SMesh::ConvertToVertData(float out[])
{
	// Track out indices separate from loop
	int outIndex = 0;
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			glm::vec3 vertPos = tris[i].vertices[j].pos;
			glm::vec3 vertColor = tris[i].mat.kd;

			// Position
			out[outIndex] = vertPos.x + pos.x;
			outIndex++;
			out[outIndex] = vertPos.y + pos.y;
			outIndex++;
			out[outIndex] = vertPos.z + pos.z;
			outIndex++;

			// Color
			out[outIndex] = glm::clamp(vertColor.x + tris[i].mat.ka.x, 0.0f, 1.0f);
			outIndex++;
			out[outIndex] = glm::clamp(vertColor.y + tris[i].mat.ka.y, 0.0f, 1.0f);
			outIndex++;
			out[outIndex] = glm::clamp(vertColor.z + tris[i].mat.ka.z, 0.0f, 1.0f);
			outIndex++;
		}
	}
}

void SMesh::ConvertToVertColorNormalData(float out[])
{
	// Track out indices separate from loop
	int outIndex = 0;
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			glm::vec3 vertPos = tris[i].vertices[j].pos;
			glm::vec3 vertNorm = tris[i].vertices[j].normal;
			glm::vec3 vertColor = tris[i].mat.kd;

			// Position
			out[outIndex] = vertPos.x + pos.x;
			outIndex++;
			out[outIndex] = vertPos.y + pos.y;
			outIndex++;
			out[outIndex] = vertPos.z + pos.z;
			outIndex++;

			// Normal
			out[outIndex] = vertNorm.x;
			outIndex++;
			out[outIndex] = vertNorm.y;
			outIndex++;
			out[outIndex] = vertNorm.z;
			outIndex++;

			// Color
			out[outIndex] = glm::clamp(vertColor.x + tris[i].mat.ka.x, 0.0f, 1.0f);
			outIndex++;
			out[outIndex] = glm::clamp(vertColor.y + tris[i].mat.ka.y, 0.0f, 1.0f);
			outIndex++;
			out[outIndex] = glm::clamp(vertColor.z + tris[i].mat.ka.z, 0.0f, 1.0f);
			outIndex++;
		}
	}
}

void SMesh::AddTri(STriangle _tri)
{
	tris.push_back(_tri);
}

void SMesh::SetTri(size_t index, STriangle _tri)
{
	tris[index] = _tri;
}

STriangle SMesh::GetTri(size_t index)
{
	return tris[index];
}

void SMesh::ClearTris() {
	tris.clear();
}

int SMesh::GetVertCount()
{
	return (int)tris.size() * 3;
}

int SMesh::GetTriCount()
{
	return (int)tris.size();
}

void SMesh::RecalculateNormals()
{
	// Reset normals for each tri
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			tris[i].vertices[j].normal = glm::vec3(0, 0, 0);
		}
	}

	// Calculate normals for each tri
	for (int i = 0; i < tris.size(); i++) {
		glm::vec3 triNorm = tris[i].CalcNormal();

		for (int j = 0; j < TRI_VERTS; j++) {
			tris[i].vertices[j].normal += triNorm;
		}
	}

	// Normalize normals for each vertex
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			tris[i].vertices[j].normal = glm::normalize(tris[i].vertices[j].normal);
		}
	}
}

int SMesh::GetVertexModel() { return 0; }

SMesh::~SMesh()
{
	ClearTris();
}

// IMesh definitions
// -----------------
void IMesh::ConvertToVertData(float out[])
{
	// Track out indices separate from loop
	size_t outIndex = 0;
	for (int i = 0; i < lastVertIndex; i++) {
		glm::vec3 vertPos = verts[i + 1].pos;
		out[outIndex] = vertPos.x + pos.x;
		outIndex++;
		out[outIndex] = vertPos.y + pos.y;
		outIndex++;
		out[outIndex] = vertPos.z + pos.z;
		outIndex++;

		// Color
		out[outIndex] = glm::clamp((float)(1 - i % 3), 0.0f, 1.0f);
		outIndex++;
		out[outIndex] = glm::clamp((float)(1 - (i + 1) % 3), 0.0f, 1.0f);
		outIndex++;
		out[outIndex] = glm::clamp((float)(1 - (i + 2) % 3), 0.0f, 1.0f);
		outIndex++;
	}
}

void IMesh::ConvertToIndexData(unsigned int out[])
{
	// Track out indices separate from loop
	size_t outIndex = 0;
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			out[outIndex] = tris[i].vertices[j];
			outIndex++;
		}
	}
}

void IMesh::AddTri(ITriangle _tri)
{
	tris.push_back(_tri);
}

int IMesh::AddVert(Vertex _vert)
{
	return AddVert(lastVertIndex + 1, _vert);
}

int IMesh::AddVert(int _index, Vertex _vert)
{
	// Only add the vertex if it doesn't exist in the mesh yet
	if (verts.find(_index) == verts.end()) {
		verts.emplace(_index, _vert);
		lastVertIndex = std::max(lastVertIndex, _index);
	}
	return _index;
}

void IMesh::SetTri(size_t index, ITriangle _tri)
{
	tris[index] = _tri;
}

ITriangle IMesh::GetTri(size_t index)
{
	return tris[index];
}

void IMesh::ClearTris() {
	tris.clear();
	verts.clear();
}

int IMesh::GetVertCount()
{
	return (int)verts.size() * 3;
}

int IMesh::GetIndexCount()
{

	return (int)tris.size() * 3;
}

int IMesh::GetTriCount()
{
	return (int)tris.size();
}

void IMesh::RecalculateNormals()
{

}

int IMesh::GetVertexModel() { return 1; }

IMesh::~IMesh()
{
	ClearTris();
}