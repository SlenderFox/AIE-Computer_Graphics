#pragma once
#include <glm/vec3.hpp>

class DirectionalLight
{
public:
	/*
		@brief The default constructor
	*/
	DirectionalLight();

	/*
		@brief The default destructor
	*/
	~DirectionalLight();

	glm::vec3		m_direction;
	glm::vec3		m_diffuse;
	glm::vec3		m_specular;
};