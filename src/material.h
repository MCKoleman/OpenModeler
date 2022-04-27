#pragma once
#include "glIncludes.h"
#include <string>
#include <vector>

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

	static Material Average(std::vector<Material*>& _mats)
	{
		// Init values
		float n = 1.0f / _mats.size();
		glm::vec3 _ka = glm::vec3();
		glm::vec3 _kd = glm::vec3();
		glm::vec3 _ks = glm::vec3();
		float _ns = 0.0f;
		float _ni = 0.0f;
		float _d = 0.0f;

		// Add values
		for (int i = 0; i < _mats.size(); i++) {
			_ka += _mats[i]->ka;
			_kd += _mats[i]->kd;
			_ks += _mats[i]->ks;
			_ns += _mats[i]->ns;
			_ni += _mats[i]->ni;
			_d += _mats[i]->d;
		}

		// Average values
		return Material(_ka*n, _kd*n, _ks*n, _ns*n, _ni*n, _d*n);
	}
};