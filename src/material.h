#pragma once
#include "glIncludes.h"
#include <string>

struct Material {
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float ns;
	float ni;
	float d;
	std::string mapkd;

	void Reset();

	Material();
	Material(glm::vec3 _ka, glm::vec3 _kd);
	Material(glm::vec3 _ka, glm::vec3 _kd, std::string _mapkd);
	Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns);
	Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, std::string _mapkd);
	Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, float _ni);
	Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, float _ni, float _d);
	Material(glm::vec3 _ka, glm::vec3 _kd, glm::vec3 _ks, float _ns, float _ni, float _d, std::string _mapkd);
};