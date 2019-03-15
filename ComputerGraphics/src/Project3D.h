#pragma once
#include "Application.h"
#include <glm/ext.hpp>

class Project3D : public Application
{
public:
	Project3D();
	virtual ~Project3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float pDeltaTime);
	virtual void draw();

protected:
	glm::mat4		m_view;
	glm::mat4		m_projection;
};