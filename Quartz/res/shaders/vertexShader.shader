#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

//out vec3 color;
out vec2 v_texCoords;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ProjectionMatrix;

void main(void) {
	//gl_Position = vec4(textureCoords, 0.0f, 1.0f);
	gl_Position = u_ProjectionMatrix * u_TransformationMatrix * position;
	//color = vec3(position.x + 0.5, 1.0, position.y + 0.5);
	v_texCoords = texCoords;
}