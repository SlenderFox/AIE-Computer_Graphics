#pragma once
#include "Camera.h"

struct GLFWwindow;

class FlyCamera : public Camera
{
public:
	/*
		@brief The default constructor
	*/
	FlyCamera();

	/*
		@brief A constructor that takes in a horizontal and vertical speed
		@param The horizontal speed for the camera
		@param The vertical speed for the camera
	*/
	FlyCamera(float pHSpeed, float pVSpeed);

	/*
		@brief The default destructor
	*/
	~FlyCamera();

	/*
		@brief Called once per frame
		@param Deltatime, the time in between frames
		@param A pointer to the game window
	*/
	virtual void update(float pDeltaTime, GLFWwindow* pWindow);

	/*
		@brief Sets the horizontal speed of the camera
		@param The desired horizontal speed
	*/
	void setHSpeed(const float pSpeed) { m_hSpeed = pSpeed; }

	/*
		@brief Returns the horizontal speed of the camera
		@return The horizontal speed of the camera
	*/
	float getHSpeed() const { return m_hSpeed; }

	/*
		@brief Sets the vertical speed of the camera
		@param The desired vertical speed
	*/
	void setVSpeed(const float pSpeed) { m_vSpeed = pSpeed; }

	/*
		@brief Returns the vertical speed of the camera
		@return The vertical speed of the camera
	*/
	float getVSpeed() const { return m_vSpeed; }

private:
	float			m_hSpeed;		// The cameras horizontal speed
	float			m_vSpeed;		// The cameras vertical speed
};