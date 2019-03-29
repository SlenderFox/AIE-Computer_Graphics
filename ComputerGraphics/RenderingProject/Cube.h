#pragma once
#include <glm/ext.hpp>

struct KeyFrame
{
	glm::vec3 position;
	glm::quat rotation;
};

class Cube
{
public:
	Cube();
	~Cube();

	void update(float pDeltaTime);

private:
	KeyFrame		m_positions[2];
};