#pragma once
#include "triangle.h"
#include <vector>
#include <unordered_map>
const float MIN_SCALE = 0.0000001f;

class Mesh {
protected:
	// Direct values
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	// Calculated values
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 forward = glm::vec3(0.0f, 1.0f, 0.0f);
public:
	Material defaultMat = Material();

	// Calculates the basis of the mesh
	void CalcBasis();

	// Getter functions
	// Returns the up vector of this mesh
	glm::vec3 GetUp();
	// Returns the right vector of this mesh
	glm::vec3 GetRight();
	// Returns the forward vector of this mesh
	glm::vec3 GetForward();
	// Returns the position of the mesh
	glm::vec3 GetPos();
	// Returns the rotation of the mesh
	glm::vec3 GetRotation();
	// Returns the scale of the mesh
	glm::vec3 GetScale();

	// Setter functions
	// Translate the mesh by the given vector
	void Translate(glm::vec3 _deltaPos);
	// Rotates the mesh by the given vector
	void Rotate(glm::vec3 _deltaRot);
	// Scales the mesh by the given vector
	void Scale(glm::vec3 _deltaScale);
	// Sets the position of the mesh to the given position
	void SetPos(glm::vec3 _pos);
	// Sets the rotation of the mesh to the given rotation
	void SetRotation(glm::vec3 _rot);
	// Sets the scale of the mesh to the given scale
	void SetScale(glm::vec3 _scale);

	// Returns the size of the mesh if it was converted into a vertex array (needed for allocating memory for ConvertToVertData())
	virtual int GetVertCount() = 0;

	// Converts this mesh into a vertex array and stores it in the given array
	virtual void ConvertToVertData(float out[]) = 0;

	// Clears the mesh of all tris
	virtual void ClearTris() = 0;

	// Gets the number of tris in the mesh
	virtual int GetTriCount() = 0;

	// Vertex model of the mesh [0 for separate, 1 for indexed]
	virtual int GetVertexModel() = 0;

	// Recalculates the normals of the mesh
	virtual void RecalculateNormals() = 0;

	Mesh();
	~Mesh();
};