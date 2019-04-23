#pragma once

#include "ShaderProgram.h"

#include <iostream>

class StaticShader : public ShaderProgram {
public:
	std::string vertexFilePath;
	std::string fragmentFilePath;

	StaticShader(std::string vertexFilePath, std::string fragmentFilePath) : ShaderProgram(vertexFilePath, fragmentFilePath) {
		this->vertexFilePath = vertexFilePath;
		this->fragmentFilePath = fragmentFilePath;
	}

	~StaticShader();

protected:
	void bindAttributes();

private:
};