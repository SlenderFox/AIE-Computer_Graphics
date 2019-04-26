#pragma once
#include <glm/ext.hpp>
#include "Input.h"

struct GLFWwindow;

class Camera
{
public:
	/*
		@brief Default constructor
	*/
	Camera();

	/*
		@brief Default destructor
	*/
	~Camera();

	/*
		@brief A virtual function that is called once per frame
		@param Deltatime, the time in between frames
		@param A pointer to the game window
	*/
	virtual void update(float pDeltatime, GLFWwindow* pWindow) = 0;

	/*
		@brief Changes changes the perspective of the camera
		@param The desired field of view of the camera
		@param The aspect ratio of the camera
		@param The nearest objects rendered in the camera
		@param The furthest objects rendered in the camera
	*/
	void setPerspective(const float pFov, const float pAspectRatio, const float pNear, const float pFar);

	/*
		@brief Changes the location and look direction of the camera
		@param The location the camera will be looking from
		@param The location the camera will be looking to
		@param The up direction for the camera
	*/
	void setLookAt(const glm::vec3 pFrom, const glm::vec3 pTo, const glm::vec3 pUp);

	/*
		@brief Changes the position of the camera without changing anything else
		@param The desired position of the camera
	*/
	void setPosition(const glm::vec3 pPosition);

	/*
		@brief Changes the rotation of the camera without changing anything else
		@param The desired rotation of the camera
	*/
	void setRotation(glm::mat3 pRotations);

	/*
		@brief Returns the world transform of the camera
		@return The world transform of the camera
	*/
	glm::mat4 getWorldTransform() const { return m_worldTransform; }

	/*
		@brief Returns the view transform of the camera
		@return The view transform of the camera
	*/
	glm::mat4 getView() const { return m_viewTransform; }

	/*
		@brief Returns the projection transform of the camera
		@return The projection transform of the camera
	*/
	glm::mat4 getProjection() const { return m_projectionTransform; }

	/*
		@brief Returns the projectionview transform of the camera
		@return The projectionview transform of the camera
	*/
	glm::mat4 getProjectionView() const { return m_projectionView; }

	/*
		@brief Returns the position of the camera
		@return The position of the camera
	*/
	glm::vec3 getPosition() const { return m_worldTransform[3]; }

protected:
	/*
		@brief Updatest the projectionview transform for the camera
	*/
	void updateProjectionViewTransform();

	glm::mat4		m_worldTransform;
	glm::mat4		m_viewTransform;
	glm::mat4		m_projectionTransform;
	glm::mat4		m_projectionView;
};