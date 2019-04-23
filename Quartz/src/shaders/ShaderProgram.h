#pragma once

#include <string>

class ShaderProgram {
public:
	ShaderProgram(std::string& vertexFilePath, std::string& fragmentFilePath);
	~ShaderProgram();
	void start();
	void stop();
	void cleanUp();

protected:
	virtual void bindAttributes() = 0;
	void bindAttribute(int attribute, const char* variableName);

private:
	int programID;
	int vertexShaderID;
	int fragmentShaderID;

	static int loadShader(const std::string& filePath, unsigned int type);
};