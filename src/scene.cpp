#include "scene.h"

void Scene::GetVAO(float* vertices, int vertsSize, unsigned int* indices, int indicesSize)
{
	std::unordered_map<int, Vertex> verts = curMesh->GetVerts();
	std::vector<Triangle> tris;
	curMesh->GetTris(tris);
	glm::vec3 pos = curMesh->GetPos();
	std::cout << "Writing " << vertsSize << " vertices to VAO, " << verts.size() << " exist" << std::endl;
	std::cout << "Writing " << indicesSize << " indices to VAO, " << tris.size() << " exist" << std::endl;

	int tempHighIndex = -1;
	// Track out indices separate from loop
	for (int i = 0; i < verts.size(); i++) {
		glm::vec3 vertPos = verts[i].pos;
		glm::vec3 vertNorm = verts[i].normal;

		// Get all mats for vertex
		std::vector<std::string> _matKeys;
		std::vector<Material*> _mats;
		curMesh->GetMatsForVert(_matKeys, i);
		for (int j = 0; j < _matKeys.size(); j++) {
			_mats.push_back(mats->Get(_matKeys[j]));
		}
		Material vertMat = Material::Average(_mats);

		// Position
		// For every vertex, 9 elements are stored, so the array index is 9*i + <elem pos>
		vertices[9 * i + 0] = vertPos.x;
		vertices[9 * i + 1] = vertPos.y;
		vertices[9 * i + 2] = vertPos.z;

		// Normal
		vertices[9 * i + 3] = vertNorm.x;
		vertices[9 * i + 4] = vertNorm.y;
		vertices[9 * i + 5] = vertNorm.z;

		// Color
		vertices[9 * i + 6] = glm::clamp(vertMat.kd.r + vertMat.ka.r, 0.0f, 1.0f);
		vertices[9 * i + 7] = glm::clamp(vertMat.kd.g + vertMat.ka.g, 0.0f, 1.0f);
		vertices[9 * i + 8] = glm::clamp(vertMat.kd.b + vertMat.ka.b, 0.0f, 1.0f);

		tempHighIndex = 9 * i + 8;
	}
	std::cout << "Highest element written to vertices: " << tempHighIndex << std::endl;

	// Track out indices separate from loop
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			indices[i*TRI_VERTS + j] = tris[i].vertices[j];
			tempHighIndex = i * TRI_VERTS + j;
		}
	}
	std::cout << "Highest element written to indices: " << tempHighIndex << std::endl;
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
}