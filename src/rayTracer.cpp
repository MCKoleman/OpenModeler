#include "rayTracer.h"
#include "openHelper.h"

//Returns a view ray
Ray RayTracer::generateRay(Scene* scene, float u, float v, bool print)
{
	Camera* camera = scene->GetCamera();

	glm::vec3 eyePos = camera->pos;
	glm::vec3 lookAt = camera->dir;
	glm::vec3 upVect = camera->up;

	glm::vec3 wVect = -lookAt;
	glm::vec3 uVect = glm::normalize(glm::cross(wVect, upVect));
	glm::vec3 vVect = glm::normalize(glm::cross(wVect, uVect));

	glm::vec3 origin = camera->pos;
	//glm::vec3 origin = scene->GetInvMVP() * glm::vec4(1);
	glm::vec3 direction = -(glm::vec3(scene->GetInvMVP() * glm::vec4(u, v, -1, 1)));
	//direction = glm::normalize(origin - direction);
	if (print) {
		std::cout << "InvMVP0: [" << scene->GetInvMVP()[0].r << ", " << scene->GetInvMVP()[1].r << ", " << scene->GetInvMVP()[2].r << ", " << scene->GetInvMVP()[3].r << "]\n";
		std::cout << "InvMVP1: [" << scene->GetInvMVP()[0].g << ", " << scene->GetInvMVP()[1].g << ", " << scene->GetInvMVP()[2].g << ", " << scene->GetInvMVP()[3].g << "]\n";
		std::cout << "InvMVP2: [" << scene->GetInvMVP()[0].b << ", " << scene->GetInvMVP()[1].b << ", " << scene->GetInvMVP()[2].b << ", " << scene->GetInvMVP()[3].b << "]\n";
		std::cout << "InvMVP3: [" << scene->GetInvMVP()[0].a << ", " << scene->GetInvMVP()[1].a << ", " << scene->GetInvMVP()[2].a << ", " << scene->GetInvMVP()[3].a << "]\n";

		std::cout << "Generating ray from [" << origin.x << ", " << origin.y << ", " << origin.z << "] in direction [" 
			<< direction.x << ", " << direction.y << ", " << direction.z << "]\n";
		std::cout << "Camera info: Pos [" << camera->pos.x << ", " << camera->pos.y << ", " << camera->pos.z << "], Direction ["
			<< camera->dir.x << ", " << camera->dir.y << ", " << camera->dir.z << "]\n";
	}

	return Ray(origin, direction);
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
	
	if (foundTriangle.vertices[0].id < 0) {
		return scene->bgColor;
	}
	else {
		Material* mat = scene->GetMats()->Get(foundTriangle.mat);
		Light* light = scene->GetLight();

		glm::vec3 p = r.origin + (r.GetT(foundTriangle) * r.direction);
		glm::vec3 n = foundTriangle.normal;
		glm::vec3 h = glm::normalize(bisector(p, -light->dir));

		glm::vec3 ambient = mat->ka * light->ka;
		glm::vec3 diffuse = mat->kd * glm::max(0.0f, glm::dot(n, glm::normalize(-light->dir)));
		glm::vec3 specular = mat->ks * (float)glm::pow(glm::max(0.0f, glm::dot(n, h)), 50);

		return glm::clamp(ambient + light->ks * (diffuse + specular), 0.0f, 255.0f);
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
	scene->CalcInvMVP();
	glm::vec3 highestDir = glm::vec3(-10000);
	glm::vec3 lowestDir = glm::vec3(10000);

	for (int i = 0; i < SCR_HEIGHT; i++)
	{
		for (int j = 0; j < SCR_WIDTH; j++)
		{
			float left = -1.0f;
			float right = 1.0f;
			float top = 1.0f;
			float bottom = -1.0f;

			float u = left + (right - left) * (j + 0.5f) / (float)SCR_WIDTH;
			float v = bottom + (top - bottom) * (i + 0.5f) / (float)SCR_HEIGHT;

			Ray viewRay = generateRay(scene, u, v, false);
			result[i * SCR_WIDTH + j] = glm::vec4(getPixelColor(scene, viewRay, 0), 255.0f);

			lowestDir = glm::min(lowestDir, viewRay.direction);
			highestDir = glm::max(highestDir, viewRay.direction);
		}
	}
	glm::vec3 dirDiff = highestDir - lowestDir;
	//std::cout << "Difference between directions: [" << dirDiff.x << ", " << dirDiff.y << ", " << dirDiff.z << "]\n";
	//std::cout << "Highest direction: [" << highestDir.x << ", " << highestDir.y << ", " << highestDir.z << "]\n";
	//std::cout << "Lowest direction: [" << lowestDir.x << ", " << lowestDir.y << ", " << lowestDir.z << "]\n";
	std::cout << "Finished rendering scene\n";
}