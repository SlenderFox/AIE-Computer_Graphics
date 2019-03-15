#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setPerspective(const float pFov, const float pAspectRatio, const float pNear, const float pFar)
{
}

void Camera::setLookAt(const glm::vec3 pFrom, const glm::vec3 pTo, const glm::vec3 pUp)
{
	m_viewTransform = glm::lookAt(pFrom, pTo, pUp);
}

void Camera::setPosition(const glm::vec3 pPosition)
{
	m_worldTransform = { glm::vec4(0), glm::vec4(0), glm::vec4(0), glm::vec4(pPosition, 0) };
}

glm::mat4 Camera::getWorldTransform() const
{
	return m_worldTransform;
}

glm::mat4 Camera::getView() const
{
	return m_viewTransform;
}

glm::mat4 Camera::getProjection() const
{
	return m_projectionTransform;
}

glm::mat4 Camera::getProjectionView() const
{
	return m_projectionView;
}

void Camera::updateProjectionViewTransform()
{
}