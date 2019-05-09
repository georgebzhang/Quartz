#version 330

in vec3 position;
out vec3 texCoords;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

void main(void) {

	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(position, 1.0);
	texCoords = position;
}