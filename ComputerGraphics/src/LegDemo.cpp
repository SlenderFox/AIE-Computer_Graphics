#include "LegDemo.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Gizmos.h"

LegDemo::LegDemo()
{
	// Initialisation for the walking leg demo
	// Hip
	m_hipFrames[0].position = glm::vec3(5, 8, 0);
	m_hipFrames[0].rotation = glm::quat(glm::vec3(1, 0, 0));
	m_hipFrames[1].position = glm::vec3(5, 8, 0);
	m_hipFrames[1].rotation = glm::quat(glm::vec3(-1, 0, 0));

	// Knee
	m_kneeFrames[0].position = glm::vec3(0, -2.0f, 0);
	m_kneeFrames[0].rotation = glm::quat(glm::vec3(1, 0, 0));
	m_kneeFrames[1].position = glm::vec3(0, -2.0f, 0);
	m_kneeFrames[1].rotation = glm::quat(glm::vec3(0, 0, 0));

	// Ankle
	m_ankleFrames[0].position = glm::vec3(0, -2.0f, 0);
	m_ankleFrames[0].rotation = glm::quat(glm::vec3(0.5f, 0, 0));
	m_ankleFrames[1].position = glm::vec3(0, -2.0f, 0);
	m_ankleFrames[1].rotation = glm::quat(glm::vec3(0, 0, 0));
}

LegDemo::LegDemo(glm::vec3 pHipPosition)
{
	// Initialisation for the walking leg demo
	// Hip
	m_hipFrames[0].position = pHipPosition;
	m_hipFrames[0].rotation = glm::quat(glm::vec3(1, 0, 0));
	m_hipFrames[1].position = pHipPosition;
	m_hipFrames[1].rotation = glm::quat(glm::vec3(-1, 0, 0));

	// Knee
	m_kneeFrames[0].position = glm::vec3(0, -2.0f, 0);
	m_kneeFrames[0].rotation = glm::quat(glm::vec3(1, 0, 0));
	m_kneeFrames[1].position = glm::vec3(0, -2.0f, 0);
	m_kneeFrames[1].rotation = glm::quat(glm::vec3(0, 0, 0));

	// Ankle
	m_ankleFrames[0].position = glm::vec3(0, -2.0f, 0);
	m_ankleFrames[0].rotation = glm::quat(glm::vec3(0.5f, 0, 0));
	m_ankleFrames[1].position = glm::vec3(0, -2.0f, 0);
	m_ankleFrames[1].rotation = glm::quat(glm::vec3(0, 0, 0));
}

LegDemo::~LegDemo()
{
}

void LegDemo::update(float pDeltaTime, float pTimeStep)
{
	// Animating the hip
	glm::vec3 hipLerp = (1.0f - pTimeStep) * (m_hipFrames[0].position)
		+ (pTimeStep * (m_hipFrames[1].position));
	glm::quat hipSlerp = glm::slerp(m_hipFrames[0].rotation, m_hipFrames[1].rotation, pTimeStep);
	m_hipBone = glm::translate(hipLerp) * glm::toMat4(hipSlerp);

	// Animating the knee
	glm::vec3 kneeLerp = (1.0f - pTimeStep) * (m_kneeFrames[0].position)
		+ (pTimeStep * (m_kneeFrames[1].position));
	glm::quat kneeSlerp = glm::slerp(m_kneeFrames[0].rotation, m_kneeFrames[1].rotation, pTimeStep);
	m_kneeBone = glm::translate(kneeLerp) * glm::toMat4(kneeSlerp);

	// Animating the ankle
	glm::vec3 ankleLerp = (1.0f - pTimeStep) * (m_ankleFrames[0].position)
		+ (pTimeStep * (m_ankleFrames[1].position));
	glm::quat ankleSlerp = glm::slerp(m_ankleFrames[0].rotation, m_ankleFrames[1].rotation, pTimeStep);
	m_ankleBone = glm::translate(ankleLerp) * glm::toMat4(ankleSlerp);

	// Updating the children
	m_kneeBone = m_hipBone * m_kneeBone;
	m_ankleBone = m_kneeBone * m_ankleBone;
	glm::vec3 hipPos(m_hipBone[3].x, m_hipBone[3].y, m_hipBone[3].z);
	glm::vec3 kneePos(m_kneeBone[3].x, m_kneeBone[3].y, m_kneeBone[3].z);
	glm::vec3 anklePos(m_ankleBone[3].x, m_ankleBone[3].y, m_ankleBone[3].z);

	// Draws all the cubes in
	glm::vec4 half(0.5f);
	glm::vec4 pink(1, 0, 1, 1);
	//aie::Gizmos::addTransform(m_hipBone);
	//aie::Gizmos::addTransform(m_kneeBone);
	//aie::Gizmos::addTransform(m_ankleBone);
	aie::Gizmos::addAABBFilled(hipPos, half, pink, &m_hipBone);
	aie::Gizmos::addAABBFilled(kneePos, half, pink, &m_kneeBone);
	aie::Gizmos::addAABBFilled(anklePos, half, pink, &m_ankleBone);
}