#include "rayTracer.h"

//Ray object constructor
Ray::Ray(glm::vec3 origin, glm::vec3 direction) 
{
	this->origin = origin;
	this->direction = direction;
}

//Returns a view ray
Ray RayTracer::generateRay(Camera* camera, float u, float v)
{
	glm::vec3 eyePos = camera->pos;
	glm::vec3 lookAt = camera->dir;
	glm::vec3 upVect = glm::vec3(0, 1, 0);

	glm::vec3 wVect = -lookAt;
	glm::vec3 uVect = glm::normalize(glm::cross(wVect, upVect));
	glm::vec3 vVect = glm::normalize(glm::cross(wVect, uVect));

	return Ray(eyePos, (-1.0f * wVect + u * uVect + v * vVect));
}

//Returns bisector of given vectors
glm::vec3 RayTracer::bisector(glm::vec3 a, glm::vec3 b)
{
	return (a + b) / length(a + b);
}

//Returns normal of triangle
glm::vec3 RayTracer::normal(std::vector<glm::vec3>& vPos)
{
	glm::vec3 A = vPos[1] - vPos[0];
	glm::vec3 B = vPos[2] - vPos[0];
	return glm::normalize(glm::cross(A, B));
}

//Returns the t value of the given triangle with respect to the given ray
float RayTracer::get_t(std::vector<glm::vec3>& vPos, Ray& r)
{
	return glm::dot((vPos[0] - r.origin), normal(vPos)) / glm::dot(r.direction, normal(vPos));
}

//Returns true if the given ray intersects the given triangle
bool RayTracer::intersectTriangle(std::vector<glm::vec3>& vPos, Ray& r)
{
	float t = get_t(vPos, r);
	glm::vec3 x = r.origin + (t * r.direction);

	if (t < 0)
		return false;

	float check1 = glm::dot(glm::cross((vPos[1] - vPos[0]), (x - vPos[0])), normal(vPos));
	float check2 = glm::dot(glm::cross((vPos[2] - vPos[1]), (x - vPos[1])), normal(vPos));
	float check3 = glm::dot(glm::cross((vPos[0] - vPos[2]), (x - vPos[2])), normal(vPos));

	if (!(check1 > 0))
		return false;
	if (!(check2 > 0))
		return false;
	if (!(check3 > 0))
		return false;

	return true;
}

//Returns the key of the mesh and the triangle number within that mesh of the closest triangle to the screen
Strint RayTracer::getClosestTriangle(std::unordered_map<std::string, Mesh*>& meshes, Ray& r)
{
	float t = 100;
	std::string meshKey = "NULL";
	int triangleIndex = -1;

	for (auto iter = meshes.begin(); iter != meshes.end(); iter++) {
		Mesh* mesh = iter->second;

		auto verts = mesh->GetVerts();
		auto tris = mesh->GetTris();

		for (int i = 0; i < tris.size(); i++)
		{
			std::vector<glm::vec3> positions;
			positions.push_back(verts.at(tris[i].vertices[0]).pos);
			positions.push_back(verts.at(tris[i].vertices[1]).pos);
			positions.push_back(verts.at(tris[i].vertices[2]).pos);

			if (intersectTriangle(positions, r))
			{
				float t2 = get_t(positions, r);
				if (t2 <= t)
				{
					meshKey = iter->first;
					triangleIndex = i;
					t = t2;
				}
			}
		}
	}

	return Strint(triangleIndex, meshKey);
}



//Returns the color of the current pixel with the given ray
glm::vec3 RayTracer::getPixelColor(Scene* scene, Ray& r, int count)
{
	Strint foundTriangle = getClosestTriangle(scene->GetMeshes()->GetAll(), r);
	
	if (foundTriangle.id == -1)
		return scene->bgColor;
	else
	{
		Mesh* mesh = scene->GetMeshes()->Get(foundTriangle.str);
		Triangle triangle = mesh->GetTri(foundTriangle.id);
		Material* mat = scene->GetMats()->Get(triangle.mat);

		auto verts = mesh->GetVerts();

		std::vector<glm::vec3> positions;
		positions.push_back(verts.at(triangle.vertices[0]).pos);
		positions.push_back(verts.at(triangle.vertices[1]).pos);
		positions.push_back(verts.at(triangle.vertices[2]).pos);

		glm::vec3 p = r.origin + (get_t(positions, r) * r.direction);
		glm::vec3 n = normal(positions);
		glm::vec3 h = bisector(p, -scene->GetLight()->dir);

		// TODO: Perform color calculation and return color
	}
}

//Returns a pointer to an array that defines each pixel in the ray traced scene
glm::vec3* RayTracer::RayTrace(Scene* scene)
{
	Camera* camera = scene->GetCamera();
	glm::vec3* image = new glm::vec3[SCR_WIDTH * SCR_HEIGHT];

	float left = -1;
	float right = 1;
	float top = 1;
	float bottom = -1;

	for (int i = 0; i < SCR_HEIGHT; i++)
	{
		for (int j = 0; i < SCR_WIDTH; j++)
		{
			float u = left + (right - left) * (j + 0.5) / SCR_WIDTH;
			float v = bottom + (top - bottom) * (i + 0.5) / SCR_HEIGHT;

			Ray viewRay = generateRay(scene->GetCamera(), u, v);

			int index = i * SCR_WIDTH + j;

			image[index] = getPixelColor(scene, viewRay, 0);
		}
	}

	return image;
}