#include "ShaderProgram.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string& vertexFilePath, std::string& fragmentFilePath) {
	vertexShaderID = loadShader(vertexFilePath, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::start() {
	glUseProgram(programID);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::bindAttribute(int attribute, const char* variableName) {
	glBindAttribLocation(programID, attribute, variableName);
}

int ShaderProgram::loadShader(const std::string& filePath, unsigned int type) {
	std::ifstream stream(filePath);

	std::string line;
	std::stringstream ss;

	while (getline(stream, line)) {
		ss << line << '\n';
	}

	//ss << '\0';

	//std::cout << ss.str() << std::endl;
	//std::cin.get();

	std::string src = ss.str();

	const char* source = src.c_str();

	int shaderID = glCreateShader(type);
	//glShaderSource(shaderID, 1, &source, (const int*) 0);
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shaderID);
		return 0;
	}

	return shaderID;
}

void ShaderProgram::cleanUp() {
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}
