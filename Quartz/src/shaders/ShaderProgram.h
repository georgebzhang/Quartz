#pragma once

#include <string>
#include <unordered_map>

class ShaderProgram {
public:
	ShaderProgram(std::string& vertexFilePath, std::string& fragmentFilePath);
	~ShaderProgram();
	void start();
	void stop();
	void cleanUp();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

protected:
	virtual void bindAttributes() = 0;
	void bindAttribute(int attribute, const char* variableName);

private:
	int m_ProgramID;
	int m_VertexShaderID;
	int m_FragmentShaderID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	static int loadShader(const std::string& filePath, unsigned int type);

	int GetUniformLocation(const std::string& name);
};