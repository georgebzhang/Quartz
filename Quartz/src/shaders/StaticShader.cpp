#include "StaticShader.h"

#include <iostream>

void StaticShader::bindAttributes() {
	ShaderProgram::bindAttribute(0, "position");
}

StaticShader::~StaticShader() {

}
