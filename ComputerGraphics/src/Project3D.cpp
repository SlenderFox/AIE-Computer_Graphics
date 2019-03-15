#include "Project3D.h"
#include <Gizmos.h>
#include <glm/glm.hpp>
#include "FlyCamera.h"

using aie::Gizmos;
using glm::vec3;
using glm::vec4;
using glm::mat4;

Project3D::Project3D()
{
}

Project3D::~Project3D()
{
}

bool Project3D::startup()
{
	Gizmos::create(65535U, 65535U, 255U, 255U);

	m_flyCamera = new FlyCamera(5);
	m_flyCamera->setLookAt(vec3(10, 5, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	m_flyCamera->setPerspective(glm::pi<float>() * (75.0f / 180), 16 / 9.0f, 0.1f, 1000.0f);

	return true;
}

void Project3D::shutdown()
{
}

void Project3D::update(const float pDeltaTime)
{
	Gizmos::clear();

	m_flyCamera->update(pDeltaTime, m_window);
}

void Project3D::draw()
{
	// Clear the screen before drawing to stop object persisting
	clearScreen();

	Gizmos::addTransform(mat4(1));	// Draws x y z axis marker

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::draw(m_flyCamera->getProjectionView());
}