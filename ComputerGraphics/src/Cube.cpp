#include "Cube.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Gizmos.h"

Cube::Cube()
{
	// Initialisation for the moving cube demo
	m_keyFrames[0].position = glm::vec3(-8, 1.0f, 8);
	m_keyFrames[1].position = glm::vec3(6, 1.0f, 8);
	m_keyFrames[0].rotation = glm::quat(glm::vec3(0, -1, 0));
	m_keyFrames[1].rotation = glm::quat(glm::vec3(0, 1, 0));
}

Cube::Cube(KeyFrame pKeyFrames[2])
{
	// Initialisation for the moving cube demo
	m_keyFrames[0] = pKeyFrames[0];
	m_keyFrames[1] = pKeyFrames[1];
}

Cube::~Cube()
{
}

void Cube::update(float pDeltaTime, float pTimeStep)
{
	// Moving and rotating cube
	glm::vec3 boxLerp = (1.0f - pTimeStep) * (m_keyFrames[0].position)
		+ (pTimeStep * (m_keyFrames[1].position));
	glm::quat boxSlerp = glm::slerp(m_keyFrames[0].rotation, m_keyFrames[1].rotation, pTimeStep);
	glm::mat4 boxTransform = glm::translate(boxLerp) * glm::toMat4(boxSlerp);
	//Draws the cube in
	//aie::Gizmos::addTransform(boxTransform);
	aie::Gizmos::addAABBFilled(glm::vec3(0), glm::vec3(0.5f), glm::vec4(0.55f, 0.05f, 0.05f, 1), &boxTransform);
}