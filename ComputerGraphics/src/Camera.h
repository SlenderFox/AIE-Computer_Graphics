#pragma once
#include <glm/ext.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(float pDeltatime) = 0;

	void setPerspective(const float pFov, const float pAspectRatio, const float pNear, const float pFar);
	void setLookAt(const glm::vec3 pFrom, const glm::vec3 pTo, const glm::vec3 pUp);
	void setPosition(const glm::vec3 pPosition);
	glm::mat4 getWorldTransform() const;
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
	glm::mat4 getProjectionView() const;

private:
	void updateProjectionViewTransform();

	glm::mat4		m_worldTransform;
	glm::mat4		m_viewTransform;
	glm::mat4		m_projectionTransform;
	glm::mat4		m_projectionView;
};