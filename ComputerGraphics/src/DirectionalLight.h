#pragma once
#include <glm/vec3.hpp>

class DirectionalLight
{
public:
	DirectionalLight();
	~DirectionalLight();

	glm::vec3		m_direction;
	glm::vec3		m_diffuse;
	glm::vec3		m_specular;
};