#include "Sprite.h"
#include "Vertex.h"
#include<cstddef>
#include <iostream>
#include <string>
#include "ResourceManager.h"
using namespace std;

Sprite::Sprite(float x, float y,
	float width, float height,
	GLuint vboID, string texturePath)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->vboID = vboID;
	this->texturePath = texturePath;
	this -> texture= ResourceManager::getTexture(texturePath);
}

Sprite::~Sprite()
{
	
}

void Sprite::init()
{
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}
	Vertex vertexData[6];

	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x , y + height);
	vertexData[2].setPosition(x, y );
	vertexData[3].setPosition(x, y );
	vertexData[4].setPosition(x + width, y );
	vertexData[5].setPosition(x + width, y + height);

	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 0, 255, 255);
	}
	vertexData[1].setColor(0, 255, 0, 255);
	vertexData[4].setColor(255, 0, 0, 255);

	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData , GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	if (vboID == 0) {
		std::cerr << "VBO no inicializado." << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, texture.id);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	//postion
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));
	//color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::cleanup() {
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
		vboID = 0;
	}
}