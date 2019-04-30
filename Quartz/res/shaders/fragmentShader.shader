#version 330 core

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_ToLight;

out vec4 out_Color;

uniform sampler2D u_Texture;
uniform vec3 u_LightColor;

void main(void) {
	vec3 unitNormal = normalize(v_Normal);
	vec3 unitToLight = normalize(v_ToLight);
	vec3 diffuse = max(dot(unitNormal, unitToLight), 0) * u_LightColor;
	out_Color = vec4(diffuse, 1) * texture(u_Texture, v_TexCoords);
}