#pragma once
#include "Camera.h"

struct GLFWwindow;

class FlyCamera : public Camera
{
public:
	FlyCamera();
	FlyCamera(float pHSpeed, float pVSpeed);
	~FlyCamera();

	virtual void update(float pDeltaTime, GLFWwindow* pWindow);

	void setHSpeed(const float pSpeed) { m_hSpeed = pSpeed; }
	float getHSpeed() const { return m_hSpeed; }
	void setVSpeed(const float pSpeed) { m_vSpeed = pSpeed; }
	float getVSpeed() const { return m_vSpeed; }

private:
	float			m_hSpeed;		// The cameras horizontal speed
	float			m_vSpeed;		// The cameras vertical speed
};