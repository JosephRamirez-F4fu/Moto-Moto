#pragma once
#include <GL/glew.h>
#include<string>
using namespace std;
class GLS_Program{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint vertexShaderID;
	int numAttributes;
	void compileShader(const string& shaderPath, GLuint id);

public:
	GLS_Program();
	~GLS_Program();
	void compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
	void linkShader();
	void addAttribute( string attributeName);
	void use();
	void unuse();
	GLuint getUniformLocation(const string& uniformName);
};

