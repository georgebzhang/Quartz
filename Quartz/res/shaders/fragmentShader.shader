#version 330 core

in vec4 v_Position;
in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_ToLight;
in vec3 v_LightPosition;

out vec4 out_Color;

// Camera
uniform vec3 u_CamPosition;

// Light
uniform vec3 u_I; // intensity
uniform vec3 u_LightPosition;
uniform vec3 u_Ia; // ambient color

// Texture
uniform sampler2D u_Texture;
uniform float u_ka;
uniform float u_kd;
uniform float u_ks;
uniform float u_p;

void main(void) {
	vec3 unitNormal = normalize(v_Normal);
	vec3 unitToLight = normalize(v_ToLight);
	vec4 I_falloff = vec4(u_I, 1.0) / pow(length(vec4(u_LightPosition, 1.0) - v_Position), 2);

	vec4 ambient = u_ka * vec4(u_Ia, 1.0);
	vec4 diffuse = u_kd * I_falloff * max(dot(unitNormal, unitToLight), 0);
	vec4 specular = u_ks * I_falloff * pow(max(dot(unitNormal, unitToLight), 0), u_p);
	out_Color = (ambient + diffuse) * texture(u_Texture, v_TexCoords);
	out_Color.a = 1; // needed, since u_ka, u_kd, u_ks scale alpha in above calculations
}