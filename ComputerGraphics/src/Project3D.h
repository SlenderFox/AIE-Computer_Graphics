#pragma once
#include "Application.h"
#include <glm/ext.hpp>

class FlyCamera;

struct KeyFrame
{
	glm::vec3 position;
	glm::quat rotation;
};

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
	FlyCamera*		m_flyCamera;

	glm::vec3		m_positions[2];
	glm::quat		m_rotations[2];

	KeyFrame		m_hipFrames[2];
	KeyFrame		m_kneeFrames[2];
	KeyFrame		m_ankleFrames[2];

	glm::mat4		m_hipBone;
	glm::mat4		m_kneeBone;
	glm::mat4		m_ankleBone;
};