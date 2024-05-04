#include "Camera2D.h"

Camera2D::Camera2D()
{
	scale = 1.0f;
	screenHeight = 500;
	screenWidth = 500;
	cameraMatrix = glm::mat4(1.0f);
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	needsMatrixUpdate = true;
}

Camera2D::~Camera2D()
{
}

void Camera2D::update()
{
	if(needsMatrixUpdate)
	{
		glm::vec3 translate(-position.x , -position.y , 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);
		glm::vec3 newScale(scale, scale, 0.0f);
		needsMatrixUpdate = false;

	}
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}
