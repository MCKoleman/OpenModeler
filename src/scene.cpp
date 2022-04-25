#include "scene.h"

void Scene::GetVAO(float* vertices, int vertsSize, unsigned int* indices, int indicesSize)
{
	CalcRenderTris();
	//std::cout << "Writing " << vertsSize << " vertices to VAO, " << verts.size() << " exist" << std::endl;
	//std::cout << "Writing " << indicesSize << " indices to VAO, " << tris.size() << " exist" << std::endl;

	int tempHighIndex = -1;
	int startIndex = 0;

	for (auto iter = GetMeshes()->GetAll().begin(); iter != GetMeshes()->GetAll().end(); ++iter) {
		Mesh* curMesh = iter->second;
		std::unordered_map<int, Vertex> verts = curMesh->GetVerts();
		glm::vec3 pos = curMesh->GetPos();
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
			vertices[startIndex + 9 * i + 0] = vertPos.x;
			vertices[startIndex + 9 * i + 1] = vertPos.y;
			vertices[startIndex + 9 * i + 2] = vertPos.z;

			// Normal
			vertices[startIndex + 9 * i + 3] = vertNorm.x;
			vertices[startIndex + 9 * i + 4] = vertNorm.y;
			vertices[startIndex + 9 * i + 5] = vertNorm.z;

			// Color
			vertices[startIndex + 9 * i + 6] = glm::clamp(vertMat.kd.r + vertMat.ka.r, 0.0f, 1.0f);
			vertices[startIndex + 9 * i + 7] = glm::clamp(vertMat.kd.g + vertMat.ka.g, 0.0f, 1.0f);
			vertices[startIndex + 9 * i + 8] = glm::clamp(vertMat.kd.b + vertMat.ka.b, 0.0f, 1.0f);

			tempHighIndex = 9 * i + 8;
		}
		startIndex += (int)verts.size();
	}
	std::cout << "Highest element written to vertices: " << tempHighIndex << std::endl;

	// Track out indices separate from loop
	std::vector<Triangle> tris = GetTris();
	for (int i = 0; i < tris.size(); i++) {
		for (int j = 0; j < TRI_VERTS; j++) {
			indices[i*TRI_VERTS + j] = tris[i].vertices[j];
			tempHighIndex = i * TRI_VERTS + j;
		}
	}
	std::cout << "Highest element written to indices: " << tempHighIndex << std::endl;
}

void Scene::CalcRenderTris()
{
	// Clear previous tris
	renderTris.clear();

	// Calculate new tris
	int mi = 0;
	for (auto iter = meshes->GetAll().begin(); iter != meshes->GetAll().end(); ++iter) {
		Mesh* tempMesh = meshes->Get(iter->first);
		std::vector<Triangle> tempTris;
		tempMesh->GetTris(tempTris);

		// Convert all tris to info tris
		for (int i = 0; i < tempTris.size(); i++) {
			renderTris.push_back(ITriangle(tempTris[i], tempMesh->GetVerts(), i, mi, tempTris[i].tag));
		}
		mi++;
	}

	// Ensure all tris are facing the correct way
	for (int i = 0; i < renderTris.size(); i++) {
		renderTris[i].Reorient(renderTris);
	}

	// Make tris out of render tris
	tris.clear();
	for (int i = 0; i < renderTris.size(); i++) {
		tris.push_back(Triangle(
			renderTris[i].vertices[0].id, 
			renderTris[i].vertices[1].id, 
			renderTris[i].vertices[2].id,
			renderTris[i].normal, renderTris[i].center,
			renderTris[i].mat, renderTris[i].shadingGroup, renderTris[i].tag));
	}
}

std::unordered_map<int, Vertex>& Scene::GetVerts()
{
	return verts;
}

std::vector<Triangle>& Scene::GetTris()
{
	return tris;
}

std::vector<ITriangle>& Scene::GetRenderTris()
{
	return renderTris;
}

int Scene::GetVertCount()
{
	int count = 0;
	for (auto iter = meshes->GetAll().begin(); iter != meshes->GetAll().end(); ++iter) {
		count += (int)meshes->Get(iter->first)->GetVerts().size();
	}
	return count;
}

int Scene::GetIndexCount()
{
	int count = 0;
	for (auto iter = meshes->GetAll().begin(); iter != meshes->GetAll().end(); ++iter) {
		for (int i = 0; i < meshes->Get(iter->first)->GetFaces().size(); i++) {
			// ngon will create (n-2) triangles with 3 vertices each
			count += (meshes->Get(iter->first)->GetFaces()[i].GetNumVerts() - 2) * 3;
		}
	}
	return count;
}

Camera* Scene::GetCamera() { return camera; }
Light* Scene::GetLight() { return light; }
MaterialStorage* Scene::GetMats() { return mats; }
MeshStorage* Scene::GetMeshes() { return meshes; }

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

Scene::Scene()
{
	camera = new Camera();
	light = new Light();
	mats = new MaterialStorage();
	meshes = new MeshStorage();

	meshes->AddMesh("defaultMesh", new Mesh());
}

Scene::~Scene()
{
	delete camera;
	delete light;
	delete mats;
	delete meshes;

	renderTris.clear();
	tris.clear();
	verts.clear();
}