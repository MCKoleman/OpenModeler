#include "vertex.h"

Vertex::Vertex()
{
	pos = glm::vec3();
	normal = glm::vec3();
	texture = glm::vec3();
}

Vertex::Vertex(glm::vec3 _pos, glm::vec3 _normal)
{
	pos = _pos;
	normal = _normal;
	texture = glm::vec3();
}

Vertex::Vertex(glm::vec3 _pos, glm::vec3 _normal, glm::vec3 _text)
{
	pos = _pos;
	normal = _normal;
	texture = _text;
}