#include "scene.h"

void Scene::GetVAO(float* vertices, int vertsSize, unsigned int* indices, int indicesSize)
{
	auto verts = curMesh->GetVerts();
	std::vector<Triangle> tris;
	curMesh->GetTris(tris);
	glm::vec3 pos = curMesh->GetPos();

	// Track out indices separate from loop
	size_t outVertIndex = 0;
	for (int i = 0; i < verts.size(); i++) {
		glm::vec3 vertPos = verts[i].pos;
		glm::vec3 vertNorm = verts[i].normal;
		Material* vertMat = mats->Get(tris[i].mat);

		// Position
		vertices[outVertIndex] = vertPos.x + pos.x;
		outVertIndex++;
		vertices[outVertIndex] = vertPos.y + pos.y;
		outVertIndex++;
		vertices[outVertIndex] = vertPos.z + pos.z;
		outVertIndex++;

		// Normal
		vertices[outVertIndex] = vertNorm.x;
		outVertIndex++;
		vertices[outVertIndex] = vertNorm.y;
		outVertIndex++;
		vertices[outVertIndex] = vertNorm.z;
		outVertIndex++;

		// Color
		vertices[outVertIndex] = glm::clamp(vertMat->kd.r + vertMat->ka.r, 0.0f, 1.0f);
		outVertIndex++;
		vertices[outVertIndex] = glm::clamp(vertMat->kd.g + vertMat->ka.g, 0.0f, 1.0f);
		outVertIndex++;
		vertices[outVertIndex] = glm::clamp(vertMat->kd.b + vertMat->ka.b, 0.0f, 1.0f);
		outVertIndex++;
	}

	// Track out indices separate from loop
	size_t outIndex = 0;
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			indices[outIndex] = tris[i].vertices[j];
			outIndex++;
		}
	}
}

void Scene::GetTris(std::vector<ITriangle>& outTris)
{
	for (auto iter = meshes->GetAll().begin(); iter != meshes->GetAll().end(); ++iter) {
		Mesh* tempMesh = meshes->Get(iter->first);
		std::vector<Triangle> tris;
		tempMesh->GetTris(tris);

		// Convert all tris to info tris
		for (int i = 0; i < tris.size(); i++) {
			outTris.push_back(ITriangle(tris[i], tempMesh->GetVerts()));
		}
	}
}

Camera* Scene::GetCamera() { return camera; }
Light* Scene::GetLight() { return light; }
MaterialStorage* Scene::GetMats() { return mats; }
MeshStorage* Scene::GetMeshes() { return meshes; }
Mesh* Scene::GetCurMesh() { return curMesh; }

void Scene::SetCameraFromOptions(Options* options) { camera->SetFromOptions(options); }
void Scene::SetCamera(Camera* _cam)
{
	if (camera != nullptr)
		delete camera;
	camera = _cam;
}

void Scene::SetLight(Light* _light)
{
	if (light != nullptr)
		delete light;
	light = _light;
}

void Scene::SetMats(MaterialStorage* _mats)
{
	if (mats != nullptr)
		delete mats;
	mats = _mats;
}

void Scene::SetMeshes(MeshStorage* _meshes)
{
	if (meshes != nullptr)
		delete meshes;
	meshes = _meshes;
}

void Scene::SetCurMesh(Mesh* _curMesh)
{
	if (curMesh != nullptr)
		delete curMesh;
	curMesh = _curMesh;
}

Scene::Scene()
{
	camera = new Camera();
	light = new Light();
	mats = new MaterialStorage();
	meshes = new MeshStorage();
	curMesh = new Mesh();

	meshes->AddMesh("defaultMesh", curMesh);
}

Scene::~Scene()
{
	delete camera;
	delete light;
	delete mats;
	delete meshes;
	delete curMesh;
}