#pragma once
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

/*
	@brief Used to animate between two points
*/
struct KeyFrame
{
	glm::vec3 position;
	glm::quat rotation;
};