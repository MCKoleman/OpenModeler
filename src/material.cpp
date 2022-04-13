#include "material.h"

void Material::Reset()
{
	ka = glm::vec3();
	kd = glm::vec3();
	ks = glm::vec3();
	ns = 0.0f;
	ni = 1.0f;
	d = 1.0f;
	mapkd = "";
}

Material::Material()
	: Material(glm::vec3(), glm::vec3(), glm::vec3(), 0, 1, 1, "") {}

Material::Material(glm::vec3 _ka, glm::vec3 _kd)
	: Material(_ka, _kd, glm::vec3(), 0, 1, 1, "") {}

Material::Material(glm::vec3 _ka, glm::vec3 _kd, std::string _mapkd)
	: Material(_ka, _kd, glm::vec3(), 0, 1, 1, _mapkd) {}

Material::Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns)
	: Material(_ka, _kd, _ks, _ns, 1, 1, "") {}

Material::Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, std::string _mapkd)
	: Material(_ka, _kd, _ks, _ns, 1, 1, _mapkd) {}

Material::Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, float _ni)
	: Material(_ka, _kd, _ks, _ns, _ni, 1, "") {}

Material::Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, float _ni, float _d)
	: Material(_ka, _kd, _ks, _ns, _ni, _d, "") {}

// Constructor for material
Material::Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, float _ni, float _d, std::string _mapkd)
	: ka(_ka), kd(_kd), ks(_ks), ns(_ns), ni(_ni), d(_d), mapkd(_mapkd) {}