#include "ray.h"

//Ray object constructor
Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
	this->origin = origin;
	this->direction = direction;
}

//Returns the t value of the given triangle with respect to the given ray
float Ray::GetT(ITriangle& tri)
{
	return glm::dot((tri.vertices[0].pos - origin), tri.normal) / glm::dot(direction, tri.normal);
}

//Returns true if the given ray intersects the given triangle
bool Ray::IntersectTriangle(ITriangle& tri)
{
	float t = GetT(tri);
	glm::vec3 x = origin + (t * direction);

	if (t < 0)
		return false;

	float check1 = glm::dot(glm::cross((tri.vertices[1].pos - tri.vertices[0].pos), (x - tri.vertices[0].pos)), tri.normal);
	float check2 = glm::dot(glm::cross((tri.vertices[2].pos - tri.vertices[1].pos), (x - tri.vertices[1].pos)), tri.normal);
	float check3 = glm::dot(glm::cross((tri.vertices[0].pos - tri.vertices[2].pos), (x - tri.vertices[2].pos)), tri.normal);

	if (check1 <= 0)
		return false;
	else if (check2 <= 0)
		return false;
	else if (check3 <= 0)
		return false;

	return true;
}

//Returns a pointer to the first triangle that the view ray intersects with
ITriangle* Ray::GetClosestTriangle(std::vector<ITriangle>& tris)
{
	float t = 100;
	ITriangle* closestTri = nullptr;

	for (int i = 0; i < tris.size(); i++)
	{
		if (IntersectTriangle(tris[i]))
		{
			float t2 = GetT(tris[i]);
			if (t2 <= t)
			{
				*closestTri = tris[i];
				t = t2;
			}
		}
	}

	return closestTri;
}