#pragma once
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

struct KeyFrame
{
	glm::vec3 position;
	glm::quat rotation;
};