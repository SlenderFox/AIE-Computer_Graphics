#pragma once
#include "Camera.h"

struct GLFWwindow;

class FlyCamera : public Camera
{
public:
	FlyCamera();
	FlyCamera(float pSpeed);
	~FlyCamera();

	virtual void update(float pDeltaTime, GLFWwindow* pWindow);

	void setSpeed(const float pSpeed) { m_speed = pSpeed; }

private:
	float			m_speed;
	glm::vec3	m_up;
};