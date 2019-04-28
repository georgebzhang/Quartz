#include "ShaderProgram.h"

#include "../errors/ErrorHandler.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string& vertexFilePath, std::string& fragmentFilePath) {
	m_VertexShaderID = loadShader(vertexFilePath, GL_VERTEX_SHADER);
	m_FragmentShaderID = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);
	m_ProgramID = glCreateProgram();
	GLCall(glAttachShader(m_ProgramID, m_VertexShaderID));
	GLCall(glAttachShader(m_ProgramID, m_FragmentShaderID));
	GLCall(glLinkProgram(m_ProgramID));
	GLCall(glValidateProgram(m_ProgramID));
}

ShaderProgram::~ShaderProgram() {
	GLCall(glDeleteProgram(m_ProgramID));
}

void ShaderProgram::start() {
	GLCall(glUseProgram(m_ProgramID));
}

void ShaderProgram::stop() {
	GLCall(glUseProgram(0));
}

void ShaderProgram::bindAttribute(int attribute, const char* variableName) {
	glBindAttribLocation(m_ProgramID, attribute, variableName);
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
	glDetachShader(m_ProgramID, m_VertexShaderID);
	glDetachShader(m_ProgramID, m_FragmentShaderID);
	glDeleteShader(m_VertexShaderID);
	glDeleteShader(m_FragmentShaderID);
	glDeleteProgram(m_ProgramID);
}

void ShaderProgram::SetUniform1i(const std::string & name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void ShaderProgram::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_ProgramID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}