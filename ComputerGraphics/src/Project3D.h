#pragma once
#include "Application.h"
#include <glm/ext.hpp>
#include "Shader.h"
#include "OBJMesh.h"

class FlyCamera;
class DirectionalLight;
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

	DirectionalLight*			m_light;
	glm::vec3					m_ambientLight;

	Cube*						m_cube;
	LegDemo*					m_rightLeg;
	LegDemo*					m_leftLeg;

	// Classes required for the bunny
	aie::ShaderProgram		m_bunnyShaderProgram;
	aie::OBJMesh				m_bunnyMesh;
	glm::mat4					m_bunnyTransform;

	// Classes required for the dragon
	aie::ShaderProgram		m_dragonShaderProgram;
	aie::OBJMesh				m_dragonMesh;
	glm::mat4					m_dragonTransform;

	// Classes required for the spear
	aie::ShaderProgram		m_spearShaderProgram;
	aie::OBJMesh				m_spearMesh;
	glm::mat4					m_spearTransform;
};