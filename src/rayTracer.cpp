#include "rayTracer.h"
#include "openHelper.h"

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

//Returns the color of the current pixel with the given ray
glm::vec3 RayTracer::getPixelColor(Scene* scene, Ray& r, int count)
{
	std::vector<ITriangle> tris = scene->GetRenderTris();

	ITriangle foundTriangle = r.GetClosestTriangle(tris);
	
	if (foundTriangle.vertices[0].id < 0)
		return scene->bgColor;
	else
	{
		Material* mat = scene->GetMats()->Get(foundTriangle.mat);
		Light* light = scene->GetLight();

		glm::vec3 p = r.origin + (r.GetT(foundTriangle) * r.direction);
		glm::vec3 n = foundTriangle.normal;
		glm::vec3 h = glm::normalize(bisector(p, -light->dir));

		glm::vec3 ambient = mat->ka * light->ka;
		glm::vec3 diffuse = mat->kd * glm::max(0.0f, glm::dot(n, glm::normalize(-light->dir)));
		glm::vec3 specular = mat->ks * (float)glm::pow(glm::max(0.0f, glm::dot(n, h)), 50);

		return ambient + light->ks * (diffuse + specular);
	}
}

glm::vec3 RayTracer::normal(std::vector<glm::vec3>& vPos)
{
	return glm::vec3();
}

//Returns a pointer to an array that defines each pixel in the ray traced scene
void RayTracer::RayTrace(Scene* scene, std::vector<glm::vec4>& result)
{
	std::cout << "Started rendering scene\n";
	Camera* camera = scene->GetCamera();

	for (int i = 0; i < SCR_HEIGHT; i++)
	{
		for (int j = 0; j < SCR_WIDTH; j++)
		{
			float u = (j + 0.5f) / SCR_WIDTH;
			float v = (i + 0.5f) / SCR_HEIGHT;

			Ray viewRay = generateRay(scene->GetCamera(), u, v);
			result[i * SCR_WIDTH + j] = glm::vec4(getPixelColor(scene, viewRay, 0), 255.0f);
		}
	}
	std::cout << "Finished rendering scene\n";
}