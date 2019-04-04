#include "FlyCamera.h"
#include <GLFW/glfw3.h>

FlyCamera::FlyCamera() : m_hSpeed(5), m_vSpeed(4)
{
}

FlyCamera::FlyCamera(float pHSpeed, float pVSpeed) : m_hSpeed(pHSpeed), m_vSpeed(pVSpeed)
{
}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float pDeltaTime, GLFWwindow* pWindow)
{
	// Camera movement
	// Forward
	if (glfwGetKey(pWindow, aie::INPUT_KEY_W) == GLFW_PRESS)
		setPosition(m_worldTransform[3] + m_hSpeed * -m_worldTransform[2] * pDeltaTime);
	// Backward
	if (glfwGetKey(pWindow, aie::INPUT_KEY_S) == GLFW_PRESS)
		setPosition(m_worldTransform[3] + m_hSpeed * m_worldTransform[2] * pDeltaTime);
	// Right
	if (glfwGetKey(pWindow, aie::INPUT_KEY_D) == GLFW_PRESS)
		setPosition(m_worldTransform[3] + m_hSpeed * m_worldTransform[0] * pDeltaTime);
	// Left
	if (glfwGetKey(pWindow, aie::INPUT_KEY_A) == GLFW_PRESS)
		setPosition(m_worldTransform[3] + m_hSpeed * -m_worldTransform[0] * pDeltaTime);
	// Up
	if (glfwGetKey(pWindow, aie::INPUT_KEY_E) == GLFW_PRESS)
		setPosition(m_worldTransform[3] + m_vSpeed * m_worldTransform[1] * pDeltaTime);
	// Down
	if (glfwGetKey(pWindow, aie::INPUT_KEY_Q) == GLFW_PRESS)
		setPosition(m_worldTransform[3] + m_vSpeed * -m_worldTransform[1] * pDeltaTime);

	//// CameraRotation
	//// Up
	//if (glfwGetKey(pWindow, aie::INPUT_KEY_UP) == GLFW_PRESS)
	//{

	//}

	updateProjectionViewTransform();
}