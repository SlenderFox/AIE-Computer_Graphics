#pragma once
#include "glm/ext.hpp"
#include "KeyFrame.h"

class LegDemo
{
public:
	/*
		@brief The default constructor
	*/
	LegDemo();

	/*
		@brief A constructor that takes in the position of the hip joint for the legs
	*/
	LegDemo(glm::vec3 pHipPosition);

	/*
		@brief The default destructor
	*/
	~LegDemo();

	/*
		@brief Called once per frame
		@param Deltatime, the time in between frames
		@param The sinwave used to calculate how far along the animation is
	*/
	void update(float pDeltaTime, float pTimeStep);

private:
	KeyFrame		m_hipFrames[2];
	KeyFrame		m_kneeFrames[2];
	KeyFrame		m_ankleFrames[2];

	glm::mat4		m_hipBone;
	glm::mat4		m_kneeBone;
	glm::mat4		m_ankleBone;
};