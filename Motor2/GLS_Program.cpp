#include "GLS_Program.h"
#include <vector>
#include <fstream>
#include "Error.h"
void GLS_Program::compileShader(const string& shaderPath, GLuint id)
{
	string filecontent = "";
	string line = "";
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("Failed to open " + shaderPath +
		" unavailable error");
	}
	while (getline(shaderFile, line)) {
		filecontent += line+ "\n";
	}
	shaderFile.close();
	const char* contents = filecontent.c_str();
	glShaderSource(id, 1, &contents, nullptr);
	glCompileShader(id);
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		fatalError("Shaders don't compiled" + printf("%s", &(errorLog[0])));
		glDeleteShader(id);
		return;
	}

}

GLS_Program::GLS_Program()
{
	this->numAttributes = 0;
	this->programID = 0;
	this->vertexShaderID = 0;
	this->fragmentShaderID = 0;
}


GLS_Program::~GLS_Program()
{
}

void GLS_Program::compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	programID = glCreateProgram();

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	compileShader(vertexShaderFilePath,vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);

}

void GLS_Program::linkShader()
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);
		glDeleteProgram(programID);
		fatalError("Shaders failed to link" + printf("%s",&(errorLog[0])));
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLS_Program::addAttribute( string attributeName)
{
		glBindAttribLocation(programID, numAttributes++, attributeName.c_str());

}

void GLS_Program::use()
{
	glUseProgram(programID);
	for (int i = 0; i < numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLuint GLS_Program::getUniformLocation(const string& uniformName)
{
	GLuint location = glGetUniformLocation(programID, uniformName.c_str());

	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found in shader");
	}
	return location;
}


