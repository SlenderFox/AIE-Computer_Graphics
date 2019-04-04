#pragma once
#include "glm/ext.hpp"
#include "KeyFrame.h"

class LegDemo
{
public:
	LegDemo();
	LegDemo(glm::vec3 pHipPosition);
	~LegDemo();

	void update(float pDeltaTime, float pTimeStep);

	KeyFrame		m_hipFrames[2];
	KeyFrame		m_kneeFrames[2];
	KeyFrame		m_ankleFrames[2];

	glm::mat4		m_hipBone;
	glm::mat4		m_kneeBone;
	glm::mat4		m_ankleBone;
};