#pragma once
#include<GL/glew.h>
using namespace std;
class Sprite
{
private:
	
	float vertexData;
	GLuint vboID;
public:
	Sprite(float x, float y, float width, float height, GLuint vboID);
	~Sprite();
	void init();
	void draw();
	void cleanup();
	float x, y;
	float width, height;
};
	

