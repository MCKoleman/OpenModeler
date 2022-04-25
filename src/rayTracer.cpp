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

//Returns the t value of the given triangle with respect to the given ray
float RayTracer::get_t(ITriangle& tri, Ray& r)
{
	return glm::dot((tri.vertices[0].pos - r.origin), tri.normal) / glm::dot(r.direction, tri.normal);
}

//Returns true if the given ray intersects the given triangle
bool RayTracer::intersectTriangle(ITriangle& tri, Ray& r)
{
	float t = get_t(tri, r);
	glm::vec3 x = r.origin + (t * r.direction);

	if (t < 0)
		return false;

	float check1 = glm::dot(glm::cross((tri.vertices[1].pos - tri.vertices[0].pos), (x - tri.vertices[0].pos)), tri.normal);
	float check2 = glm::dot(glm::cross((tri.vertices[2].pos - tri.vertices[1].pos), (x - tri.vertices[1].pos)), tri.normal);
	float check3 = glm::dot(glm::cross((tri.vertices[0].pos - tri.vertices[2].pos), (x - tri.vertices[2].pos)), tri.normal);

	if (!(check1 > 0))
		return false;
	if (!(check2 > 0))
		return false;
	if (!(check3 > 0))
		return false;

	return true;
}

//Returns a pointer to the first triangle that the view ray intersects with
ITriangle* RayTracer::getClosestTriangle(std::vector<ITriangle>& tris, Ray& r)
{
	float t = 100;
	ITriangle* closestTri = nullptr;

	for (int i = 0; i < tris.size(); i++)
	{
		if (intersectTriangle(tris[i], r))
		{
			float t2 = get_t(tris[i], r);
			if (t2 <= t)
			{
				*closestTri = tris[i];
				t = t2;
			}
		}
	}

	return closestTri;
}



//Returns the color of the current pixel with the given ray
glm::vec3 RayTracer::getPixelColor(Scene* scene, Ray& r, int count)
{
	std::vector<ITriangle> tris;
	scene->GetTris(tris);

	ITriangle* foundTriangle = getClosestTriangle(tris, r);
	
	if (foundTriangle == nullptr)
		return scene->bgColor;
	else
	{
		Material* mat = scene->GetMats()->Get(foundTriangle->mat);
		Light* light = scene->GetLight();

		glm::vec3 p = r.origin + (get_t(*foundTriangle, r) * r.direction);
		glm::vec3 n = foundTriangle->normal;
		glm::vec3 h = glm::normalize(bisector(p, -light->dir));

		glm::vec3 ambient = mat->ka * light->ka;
		glm::vec3 diffuse = mat->kd * glm::max(0.0f, glm::dot(n, glm::normalize(-light->dir)));
		glm::vec3 specular = mat->ks * (float)glm::pow(glm::max(0.0f, glm::dot(n, h)), 50);

		return ambient + light->ks * (diffuse + specular);
	}
}

//Returns a pointer to an array that defines each pixel in the ray traced scene
glm::vec3* RayTracer::RayTrace(Scene* scene)
{
	Camera* camera = scene->GetCamera();
	glm::vec3* image = new glm::vec3[SCR_WIDTH * SCR_HEIGHT];

	for (int i = 0; i < SCR_HEIGHT; i++)
	{
		for (int j = 0; i < SCR_WIDTH; j++)
		{
			float u = (j + 0.5) / SCR_WIDTH;
			float v = (i + 0.5) / SCR_HEIGHT;

			Ray viewRay = generateRay(scene->GetCamera(), u, v);

			int index = i * SCR_WIDTH + j;

			image[index] = getPixelColor(scene, viewRay, 0);
		}
	}

	return image;
}