#pragma once
#include "Application.h"
#include <glm/ext.hpp>
#include "Shader.h"
#include "OBJMesh.h"

class FlyCamera;
class Cube;
class LegDemo;

class Project3D : public Application
{
public:
	Project3D();
	virtual ~Project3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(const float pDeltaTime);
	virtual void draw();

protected:
	FlyCamera*					m_flyCamera;

	Cube*						m_cube;
	LegDemo*					m_rightLeg;
	LegDemo*					m_leftLeg;

	aie::ShaderProgram		m_bunnyShaderProgram;
	aie::OBJMesh				m_bunnyMesh;
	glm::mat4					m_bunnyTransform;

	aie::ShaderProgram		m_spearShaderProgram;
	aie::OBJMesh				m_spearMesh;
	glm::mat4					m_spearTransform;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light							m_light;
	glm::vec3					m_ambientLight;
};