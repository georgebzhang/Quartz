#version 330

in vec3 texCoords;

uniform samplerCube u_SkyBox;

void main(void) {
	gl_FragColor = texture(u_SkyBox, texCoords);
}