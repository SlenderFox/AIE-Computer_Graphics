#include "Project3D.h"
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "FlyCamera.h"

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
	Gizmos::create(65535U, 65535U, 255U, 255U);

	// Initialisation for the moving cube demo
	m_positions[0] = vec3(-10, 1.0f, 10);
	m_positions[1] = vec3(-10, 1.0f, -10);
	m_rotations[0] = quat(vec3(0, -1, 0));
	m_rotations[1] = quat(vec3(0, 1, 0));

	// Initialisation for the walking leg demo
	// Hip
	m_hipFrames[0].position = vec3(0, 8, 0);
	m_hipFrames[0].rotation = quat(vec3(1, 0, 0));
	m_hipFrames[1].position = vec3(0, 8, 0);
	m_hipFrames[1].rotation = quat(vec3(-1, 0, 0));

	// Knee
	m_kneeFrames[0].position = vec3(0, -2.0f, 0);
	m_kneeFrames[0].rotation = quat(vec3(1, 0, 0));
	m_kneeFrames[1].position = vec3(0, -2.0f, 0);
	m_kneeFrames[1].rotation = quat(vec3(0, 0, 0));

	// Ankle
	m_ankleFrames[0].position = vec3(0, -2.0f, 0);
	m_ankleFrames[0].rotation = quat(vec3(-1, 0, 0));
	m_ankleFrames[1].position = vec3(0, -2.0f, 0);
	m_ankleFrames[1].rotation = quat(vec3(0, 0, 0));

	// Initialising flyCamera
	m_flyCamera = new FlyCamera(5, 4);
	m_flyCamera->setLookAt(vec3(10, 6, 10), vec3(0, 1, 0), vec3(0, 1, 0));
	m_flyCamera->setPerspective(glm::pi<float>() * (75.0f / 180), 16 / 9.0f, 0.1f, 1000.0f);

	return true;
}

void Project3D::shutdown()
{
}

void Project3D::update(const float pDeltaTime)
{
	Gizmos::clear();

	// Used to animate an alue between 0 and 1
	float timeSin = glm::sin((float)glfwGetTime()) * 0.5f + 0.5f;
	float timeCos = glm::cos((float)glfwGetTime()) * 0.5f + 0.5f;

	// Moving and rotating cube
	vec3 boxLerp = (1.0f - timeCos) * (m_positions[0] * 0.5f)
		+ (timeCos * (m_positions[1] * 0.5f));
	quat boxSlerp = glm::slerp(m_rotations[0], m_rotations[1], timeCos);
	mat4 boxTransform = glm::translate(boxLerp) * glm::toMat4(boxSlerp);
	//Draws the cube in
	Gizmos::addTransform(boxTransform);
	Gizmos::addAABBFilled(vec3(0), vec3(0.5f), vec4(0.55f, 0.05f, 0.05f, 1), &boxTransform);

	// Animating the hip
	vec3 hipLerp = (1.0f - timeCos) * (m_hipFrames[0].position * 0.5f)
		+ (timeCos * (m_hipFrames[1].position * 0.5f));
	quat hipSlerp = glm::slerp(m_hipFrames[0].rotation, m_hipFrames[1].rotation, timeCos);
	m_hipBone = glm::translate(hipLerp) * glm::toMat4(hipSlerp);

	// Animating the knee
	vec3 kneeLerp = (1.0f - timeCos) * (m_kneeFrames[0].position * 0.5f)
		+ (timeCos * (m_kneeFrames[1].position * 0.5f));
	quat kneeSlerp = glm::slerp(m_kneeFrames[0].rotation, m_kneeFrames[1].rotation, timeCos);
	m_kneeBone = glm::translate(kneeLerp) * glm::toMat4(kneeSlerp);

	// Animating the ankle
	vec3 ankleLerp = (1.0f - timeCos) * (m_ankleFrames[0].position * 0.5f)
		+ (timeCos * (m_ankleFrames[1].position * 0.5f));
	quat ankleSlerp = glm::slerp(m_ankleFrames[0].rotation, m_ankleFrames[1].rotation, timeCos);
	m_ankleBone = glm::translate(ankleLerp) * glm::toMat4(ankleSlerp);

	// Updating the children
	m_kneeBone = m_hipBone * m_kneeBone;
	m_ankleBone = m_kneeBone * m_ankleBone;
	vec3 hipPos(m_hipBone[3].x, m_hipBone[3].y, m_hipBone[3].z);
	vec3 kneePos(m_kneeBone[3].x, m_kneeBone[3].y, m_kneeBone[3].z);
	vec3 anklePos(m_ankleBone[3].x, m_ankleBone[3].y, m_ankleBone[3].z);

	// Draws all the cubes in
	vec4 half(0.5f);
	vec4 pink(1, 0, 1, 1);
	//Gizmos::addTransform(m_hipBone);
	//Gizmos::addTransform(m_kneeBone);
	//Gizmos::addTransform(m_ankleBone);
	Gizmos::addAABBFilled(hipPos, half, pink, &m_hipBone);
	Gizmos::addAABBFilled(kneePos, half, pink, &m_kneeBone);
	Gizmos::addAABBFilled(anklePos, half, pink, &m_ankleBone);

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

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::draw(m_flyCamera->getProjectionView());
}