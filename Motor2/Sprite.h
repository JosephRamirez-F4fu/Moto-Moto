#pragma once
#include<GL/glew.h>
#include "GLTexture.h"
#include<string>
using namespace std;
class Sprite
{
private:
	
	float vertexData;
	GLuint vboID;
	GLTexture texture;
	string texturePath;
public:
	Sprite(float x, float y,
		float width, float height,
		GLuint vboID, string texturePath);
	~Sprite();
	void init();
	void draw();
	void cleanup();
	float x, y;
	float width, height;
};
	

