#include "Shader.h"

#include "../errors/ErrorHandler.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
	m_VertexShaderID = loadShader(vertexFilePath, GL_VERTEX_SHADER);
	m_FragmentShaderID = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);
	m_ProgramID = glCreateProgram();
	GLCall(glAttachShader(m_ProgramID, m_VertexShaderID));
	GLCall(glAttachShader(m_ProgramID, m_FragmentShaderID));
	GLCall(glLinkProgram(m_ProgramID));
	GLCall(glValidateProgram(m_ProgramID));
}

Shader::~Shader() {
	unbind();
	GLCall(glDetachShader(m_ProgramID, m_VertexShaderID));
	GLCall(glDetachShader(m_ProgramID, m_FragmentShaderID));
	GLCall(glDeleteShader(m_VertexShaderID));
	GLCall(glDeleteShader(m_FragmentShaderID));
	GLCall(glDeleteProgram(m_ProgramID));
}

void Shader::bind() const {
	GLCall(glUseProgram(m_ProgramID));
}

void Shader::unbind() const {
	GLCall(glUseProgram(0));
}

int Shader::loadShader(const std::string& filePath, unsigned int type) {
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss;

	while (std::getline(stream, line)) {
		ss << line << '\n';
	}

	std::string ssource = ss.str();
	const char* csource = ssource.c_str();

	int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &csource, (const int*) 0);
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

void Shader::setUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float v0) {
	GLCall(glUniform1f(getUniformLocation(name), v0));
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
	GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform3fv(const std::string& name, glm::vec3 v) {
	GLCall(glUniform3fv(getUniformLocation(name), 1, &v[0]));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0])); // 1 matrix, false (don't need to transpose)
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_ProgramID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}