#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();
	void update();
	void init(int screenWidth, int screenHeight);
	void setPosition(const glm::vec2& newPosition) {
		position = newPosition;
		needsMatrixUpdate = true;
	}
	void setScale(float newScale) {
		scale = newScale;
		needsMatrixUpdate = true;
	}
	glm::mat4 getCameraMatrix() { 
		return cameraMatrix; 
	}


private:
	glm::vec2 position;
	float scale;
	glm::mat4 cameraMatrix;
	int screenWidth, screenHeight;
	glm::mat4 orthoMatrix;
	bool needsMatrixUpdate;
};

