#pragma once
#include "Application.h"
#include <glm/ext.hpp>

class FlyCamera;

class Project3D : public Application
{
public:
	Project3D();
	virtual ~Project3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(const float pDeltaTime);
	virtual void draw();

protected:
	FlyCamera*		m_flyCamera;
};