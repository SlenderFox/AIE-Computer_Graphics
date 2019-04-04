#include "Project3D.h"
#include <Gizmos.h>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "FlyCamera.h"
#include "Cube.h"
#include "LegDemo.h"

using aie::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

Project3D::Project3D()
{
}

Project3D::~Project3D()
{
}

bool Project3D::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	Gizmos::create(65535U, 65535U, 255U, 255U);

	m_light.diffuse = { 1, 1, 1 };
	m_light.specular = { 1, 1, 1 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f, };

	// Initialising flyCamera
	m_flyCamera = new FlyCamera(5, 4);
	m_flyCamera->setLookAt(vec3(10, 6, 10), vec3(0, 1, 0), vec3(0, 1, 0));
	m_flyCamera->setPerspective(glm::pi<float>() * (75.0f / 180), 16 / 9.0f, 0.1f, 1000.0f);

	m_cube = new Cube();
	m_rightLeg = new LegDemo(vec3(5, 8, 0));
	m_leftLeg = new LegDemo(vec3(7, 8, 0));

	// Initialising bunny shader program
	m_bunnyShaderProgram.loadShader(aie::eShaderStage::VERTEX, "../Assets/shaders/phong.vert");
	m_bunnyShaderProgram.loadShader(aie::eShaderStage::FRAGMENT, "../Assets/shaders/phong.frag");

	if (m_bunnyShaderProgram.link() == false)
	{
		printf("Bunny shader Error: %s\n", m_bunnyShaderProgram.getLastError());
		return false;
	}

	if (m_bunnyMesh.load("../Assets/stanford/Bunny.obj", false, true) == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;
	}

	m_bunnyTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, -5, 1
	};

	// Initialising spear shader program
	m_spearShaderProgram.loadShader(aie::eShaderStage::VERTEX, "../Assets/shaders/phong.vert");
	m_spearShaderProgram.loadShader(aie::eShaderStage::FRAGMENT, "../Assets/shaders/phong.frag");

	if (m_spearShaderProgram.link() == false)
	{
		printf("Spear shader Error: %s\n", m_spearShaderProgram.getLastError());
		return false;
	}

	if (m_spearMesh.load("../Assets/soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_spearTransform =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		8, 0, 0, 1
	};

	return true;
}

void Project3D::shutdown()
{
	delete m_flyCamera;
	delete m_cube;
	delete m_rightLeg;
}

void Project3D::update(const float pDeltaTime)
{
	Gizmos::clear();

	float time = (float)glfwGetTime();

	// Used to animate an alue between 0 and 1
	float cosTimeStep = glm::sin(time) * 0.5f + 0.5f;
	float sinTimeStep = glm::sin(time) * 0.5f + 0.5f;
	float invSinTimeStep = glm::sin(time) * -0.5f + 0.5f;

	m_cube->update(pDeltaTime, cosTimeStep);
	m_rightLeg->update(pDeltaTime, sinTimeStep);
	m_leftLeg->update(pDeltaTime, invSinTimeStep);

	m_light.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

	// Updates the cameras view
	m_flyCamera->update(pDeltaTime, m_window);
}

void Project3D::draw()
{
	// Clear the screen before drawing to stop object persisting
	clearScreen();

	Gizmos::addTransform(mat4(1));	// Draws x y z axis marker

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	// Creates a 10x10 grid pattern at y = 0
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	// Updating bunny shader program
	m_bunnyShaderProgram.bind();

	mat4 bunnyPV = m_flyCamera->getProjectionView() * m_bunnyTransform;
	m_bunnyShaderProgram.bindUniform("ProjectionViewModel", bunnyPV);

	// Bind light
	m_bunnyShaderProgram.bindUniform("Ia", m_ambientLight);
	m_bunnyShaderProgram.bindUniform("Id", m_light.diffuse);
	m_bunnyShaderProgram.bindUniform("Is", m_light.specular);
	m_bunnyShaderProgram.bindUniform("LightDirection", m_light.direction);

	m_bunnyShaderProgram.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));
	//m_bunnyShaderProgram.bindUniform("ModelMatrix", m_bunnyTransform);
	//m_bunnyShaderProgram.bindUniform("cameraPosition", m_flyCamera->getWorldTransform()[3]);

	// Draws bunny mesh
	m_bunnyMesh.draw();

	// Updating spear shader program
	m_spearShaderProgram.bind();

	mat4 spearPV = m_flyCamera->getProjectionView() * m_spearTransform;
	m_spearShaderProgram.bindUniform("ProjectionViewModel", spearPV);

	// Bind light
	m_spearShaderProgram.bindUniform("Ia", m_ambientLight);
	m_spearShaderProgram.bindUniform("Id", m_light.diffuse);
	m_spearShaderProgram.bindUniform("Is", m_light.specular);
	m_spearShaderProgram.bindUniform("LightDirection", m_light.direction);

	m_spearShaderProgram.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));
	//m_spearShaderProgram.bindUniform("ModelMatrix", m_spearTransform);
	//m_spearShaderProgram.bindUniform("cameraPosition", m_flyCamera->getWorldTransform()[3]);

	// Draws soulspear mesh
	m_spearMesh.draw();

	// Draws all gizmos
	Gizmos::draw(m_flyCamera->getProjectionView());
}