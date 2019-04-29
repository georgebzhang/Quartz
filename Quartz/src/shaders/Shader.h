#pragma once

#include <string>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~Shader();
	void bind() const;
	void unbind() const;

	void setUniform1i(const std::string& name, int value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

protected:
	//virtual void bindAttributes() = 0;
	//void bindAttribute(int attribute, const char* variableName);

private:
	int m_ProgramID;
	int m_VertexShaderID;
	int m_FragmentShaderID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	int loadShader(const std::string& filePath, unsigned int type);
	int getUniformLocation(const std::string& name);
};