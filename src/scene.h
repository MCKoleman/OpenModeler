#pragma once
#include "glIncludes.h"
#include "light.h"
#include "camera.h"
#include "materialStorage.h"
#include "meshStorage.h"

class Scene
{
private:
	Light* light;
	Camera* camera;
	MaterialStorage* mats;
	MeshStorage* meshes;
	Mesh* curMesh;
public:
	glm::vec3 bgColor = glm::vec3(255, 87, 51);

	void GetVAO(float* vertices, int vertsSize, unsigned int* indices, int indicesSize);

	Camera* GetCamera();
	Light* GetLight();
	MaterialStorage* GetMats();
	MeshStorage* GetMeshes();
	Mesh* GetCurMesh();

	void SetCameraFromOptions(Options* options);
	void SetCamera(Camera* _cam);
	void SetLight(Light* _light);
	void SetMats(MaterialStorage* _mats);
	void SetMeshes(MeshStorage* _meshes);
	void SetCurMesh(Mesh* _curMesh);

	Scene();
	~Scene();
};