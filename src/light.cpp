#include "light.h"

Light::Light()
	: Light(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f) {}

Light::Light(glm::vec3 _pos, glm::vec3 _dir, glm::vec3 _color, float _ka, float _ks)
	: pos(_pos), dir(_dir), color(_color), ka(_ka), ks(_ks) {}