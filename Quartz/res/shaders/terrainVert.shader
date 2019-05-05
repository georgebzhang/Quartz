#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out vec3 v_Position;
out vec2 v_TexCoords;
out vec3 v_Normal;
out float v_Visibility;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform vec3 u_LightPosition;

uniform float u_Has2DMesh; // not used in terrain shaders

const float density = 0.007;
const float gradient = 1.5;

void main(void) {
	v_Position = (u_TransformationMatrix * vec4(position, 1.0)).xyz;
	vec4 positionRelativeToCam = u_ViewMatrix * vec4(v_Position, 1.0);
	gl_Position = u_ProjectionMatrix * positionRelativeToCam;

	v_Normal = (u_TransformationMatrix * vec4(normal, 0)).xyz;
	v_TexCoords = texCoords;

	float distance = length(positionRelativeToCam.xyz);
	v_Visibility = exp(-pow((distance*density), gradient));
	v_Visibility = clamp(v_Visibility, 0, 1);
}