#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

//out vec3 color;
out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_ToLight;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform vec3 u_LightPosition;

void main(void) {
	vec4 worldPosition = u_TransformationMatrix * position;
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * worldPosition;
	v_Normal = (u_TransformationMatrix * vec4(normal, 0)).xyz;
	v_ToLight = u_LightPosition - worldPosition.xyz;
	v_TexCoords = texCoords;
}