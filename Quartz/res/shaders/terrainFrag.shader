#version 330 core

in vec3 v_Position;
in vec2 v_TexCoords;
in vec3 v_Normal;

out vec4 out_Color;

// Camera
uniform vec3 u_CamPosition;

// Light
uniform vec3 u_I; // intensity
uniform vec3 u_LightPosition;
uniform vec3 u_Ia; // ambient color

// Texture
uniform sampler2D u_Texture;
uniform float u_ka; // ambient reflection constant
uniform float u_kd; // diffuse reflection constant
uniform float u_ks; // specular reflection constant
uniform float u_p; // shininess constant

void main(void) {
	vec3 n = normalize(v_Normal);
	vec3 l = normalize(u_LightPosition - v_Position); // to light
	vec3 v = normalize(u_CamPosition - v_Position); // to camera
	vec3 h = (v + l) / length(v + l); // bisector of l and v

	vec3 I_falloff = u_I / pow(length(u_LightPosition - v_Position), 2); // intensity falls off as squared distance

	vec3 ambient = u_ka * u_Ia;
	vec3 diffuse = u_kd * I_falloff * max(dot(n, l), 0);
	vec3 specular = u_ks * I_falloff * pow(max(dot(n, h), 0), u_p);

	out_Color = (vec4(ambient, 1.0) + vec4(diffuse, 1.0)) * texture(u_Texture, v_TexCoords) + vec4(specular, 1.0);
	out_Color.a = 1; // just in case u_ka, u_kd, u_ks scale alpha in above calculations
}