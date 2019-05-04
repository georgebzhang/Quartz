#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out vec3 v_Position;
out vec2 v_TexCoords;
out vec3 v_Normal;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform vec3 u_LightPosition;

void main(void) {
	v_Position = (u_TransformationMatrix * vec4(position, 1.0)).xyz;
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(v_Position, 1.0);
	v_Normal = (u_TransformationMatrix * vec4(normal, 0)).xyz;
	v_TexCoords = texCoords;
}