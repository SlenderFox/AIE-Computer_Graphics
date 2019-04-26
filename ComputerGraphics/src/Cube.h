#pragma once
#include <glm/ext.hpp>
#include "KeyFrame.h"

class Cube
{
public:
	/*
		@brief The default constructor
	*/
	Cube();

	/*
		@brief A constructor that takes 2 points to animate between
	*/
	Cube(KeyFrame pKeyFrames[2]);

	/*
		@brief The default destructor
	*/
	~Cube();

	/*
		@brief Called once per frame
		@param Deltatime, the time in between frames
		@param The sinwave used to calculate how far along the animation is
	*/
	void update(float pDeltaTime, float pTimeStep);

private:
	KeyFrame		m_keyFrames[2];
};