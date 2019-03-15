#include "FlyCamera.h"
#include <GLFW/glfw3.h>

FlyCamera::FlyCamera() : m_speed(5)
{
}

FlyCamera::FlyCamera(float pSpeed) : m_speed(pSpeed)
{
}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float pDeltaTime, GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow, INPUT_KEY_W) == GLFW_PRESS)
	{
		setPosition(glm::vec3(5, 5, 5));
	}

	updateProjectionViewTransform();
}