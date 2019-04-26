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
	/*
	@brief Default constructor
	*/
	Project3D();

	/*
	@brief Virtual deconstructer to be overridden by derived class
	*/
	virtual ~Project3D();

	/*
		@brief An override of the virtual startup function
	*/
	virtual bool startup();

	/*
		@brief An override of the virtual shutdown function
	*/
	virtual void shutdown();

	/*
		@brief An override of the virtual update function
		@param Deltatime, the time inbetween frames
	*/
	virtual void update(const float pDeltaTime);

	/*
		@brief An override of the virtual draw function
	*/
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