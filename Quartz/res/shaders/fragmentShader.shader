#version 330 core

//in vec3 color;
in vec2 v_texCoords;

out vec4 out_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(void) {
	//out_Color = vec4(color, 1.0);
	//out_Color = u_Color;
	out_Color = texture(u_Texture, v_texCoords);
}