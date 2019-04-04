#pragma once
#include <glm/ext.hpp>
#include "KeyFrame.h"

class Cube
{
public:
	Cube();
	Cube(KeyFrame pKeyFrames[2]);
	~Cube();

	void update(float pDeltaTime, float pTimeStep);

private:
	KeyFrame		m_keyFrames[2];
};