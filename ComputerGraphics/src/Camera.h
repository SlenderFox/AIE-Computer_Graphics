#pragma once
#include <glm/ext.hpp>
#include "Input.h"

struct GLFWwindow;

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(float pDeltatime, GLFWwindow* pWindow) = 0;

	void setPerspective(const float pFov, const float pAspectRatio, const float pNear, const float pFar);
	void setLookAt(const glm::vec3 pFrom, const glm::vec3 pTo, const glm::vec3 pUp);
	void setPosition(const glm::vec3 pPosition);
	void setRotation(glm::mat3 pRotations);

	glm::mat4 getWorldTransform() const { return m_worldTransform; }
	glm::mat4 getView() const { return m_viewTransform; }
	glm::mat4 getProjection() const { return m_projectionTransform; }
	glm::mat4 getProjectionView() const { return m_projectionView; }

protected:
	void updateProjectionViewTransform();

	glm::mat4		m_worldTransform;
	glm::mat4		m_viewTransform;
	glm::mat4		m_projectionTransform;
	glm::mat4		m_projectionView;
};