#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out vec3 v_Reflection;
out vec3 v_Refraction;
out vec3 v_RefractionR;
out vec3 v_RefractionG;
out vec3 v_RefractionB;
out float v_Fresnel;

out vec3 v_Position;
out vec2 v_TexCoords;
out vec3 v_Normal;

uniform mat4 u_TransformationMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform vec3 u_LightPosition;

// Camera
uniform vec3 u_CamPosition;

//const float density = 0.007;
//const float gradient = 1.5;

const float nAir = 1;
const float nGlass = 1.51714;
const float eta = nAir / nGlass;
const float etaR = 0.65;
const float etaG = 0.67;
const float etaB = 0.69;
//const float R0 = pow(nAir - nGlass, 2) / pow(nAir + nGlass, 2);
const float R0 = pow(1 - etaG, 2) / pow(1 + etaG, 2);

void main(void) {
	vec3 w_Position = (u_TransformationMatrix * vec4(position, 1.0)).xyz;
	vec4 positionRelativeToCam = u_ViewMatrix * vec4(w_Position, 1.0);
	gl_Position = u_ProjectionMatrix * positionRelativeToCam;

	vec3 incident = normalize(w_Position - u_CamPosition);

	//n = mat3(u_ViewMatrix * u_TransformationMatrix) * n;
	vec3 n = mat3(u_TransformationMatrix) * normal; // don't know why this works instead of above
	n = normalize(n);

	v_Refraction = refract(incident, n, eta);
	v_RefractionR = refract(incident, n, etaR);
	v_RefractionG = refract(incident, n, etaG);
	v_RefractionB = refract(incident, n, etaB);
	v_Reflection = reflect(incident, n);

	v_Fresnel = R0 + (1.0 - R0) * pow((1.0 - max(0, dot(-incident, n))), 5);
	//v_Fresnel = R0 + (1.0 - R0) * pow((1.0 - dot(-incident, n)), 5.0);

	v_Position = (u_TransformationMatrix * vec4(position, 1.0)).xyz;
	v_Normal = (u_TransformationMatrix * vec4(normal, 0)).xyz;
	v_TexCoords = texCoords;

	//float distance = length(positionRelativeToCam.xyz);
	//v_Visibility = exp(-pow((distance*density), gradient));
	//v_Visibility = clamp(v_Visibility, 0, 1);
}