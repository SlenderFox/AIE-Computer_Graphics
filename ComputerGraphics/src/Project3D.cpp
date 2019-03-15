#include "Project3D.h"
#include <Gizmos.h>
#include <glm/glm.hpp>

using aie::Gizmos;

Project3D::Project3D()
{
}

Project3D::~Project3D()
{
}

bool Project3D::startup()
{
	Gizmos::create(65535U, 65535U, 255U, 255U);

	return true;
}

void Project3D::shutdown()
{
}

void Project3D::update(float pDeltaTime)
{
	Gizmos::clear();

	float fov = 110.0f;
	m_view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective((fov / 180) * glm::pi<float>(), 16 / 9.0f, 0.1f, 1000.0f);
}

void Project3D::draw()
{
	// Clear the screen before drawing to stop object persisting
	clearScreen();

	Gizmos::addTransform(glm::mat4(1));	// Draws x y z axis marker

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::draw(m_projection * m_view);
}