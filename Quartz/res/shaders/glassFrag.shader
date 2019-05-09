#version 330 core

in vec3 v_Refraction;
in vec3 v_RefractionR;
in vec3 v_RefractionG;
in vec3 v_RefractionB;
in vec3 v_Reflection;
in float v_Fresnel;

in vec3 v_Position;
in vec2 v_TexCoords;
in vec3 v_Normal;

// Light
uniform vec3 u_I; // intensity
uniform vec3 u_LightPosition;
uniform vec3 u_Ia; // ambient color

// Camera
uniform vec3 u_CamPosition;

// Texture
uniform sampler2D u_Texture;
uniform float u_ka; // ambient reflection constant
uniform float u_kd; // diffuse reflection constant
uniform float u_ks; // specular reflection constant
uniform float u_p; // shininess constant

uniform vec3 u_SkyColor;

uniform samplerCube u_SkyBox;

void main(void) {
	vec3 n = normalize(v_Normal);
	vec3 l = normalize(u_LightPosition - v_Position); // to light
	vec3 v = normalize(u_CamPosition - v_Position); // to camera
	vec3 h = (v + l) / length(v + l); // bisector of l and v

	vec3 I_falloff = u_I / pow(length(u_LightPosition - v_Position), 2); // intensity falls off as squared distance

	vec3 ambient = u_ka * u_Ia;
	vec3 diffuse = u_kd * I_falloff * max(dot(n, l), 0);
	vec3 specular = u_ks * I_falloff * pow(max(dot(n, h), 0), u_p);

	vec4 texColor = texture(u_Texture, v_TexCoords);
	//if (texColor.a < 0.5) discard;

	vec4 total = (vec4(ambient, 1) + vec4(diffuse, 1) + vec4(specular, 1));
	total.a = 0.5;
	//gl_FragColor = (vec4(ambient, 1) + vec4(diffuse, 1) + vec4(specular, 1)) * texColor;
	//gl_FragColor.a = 1; // just in case u_ka, u_kd, u_ks scale alpha in above calculations
	//gl_FragColor = mix(vec4(u_SkyColor, 1), gl_FragColor, v_Visibility);

	//vec4 refractionColor = texture(u_SkyBox, normalize(v_Refraction));
	vec4 refractionColor;
	refractionColor.r = texture(u_SkyBox, normalize(v_RefractionR)).r;
	refractionColor.g = texture(u_SkyBox, normalize(v_RefractionG)).g;
	refractionColor.b = texture(u_SkyBox, normalize(v_RefractionB)).b;
	vec4 reflectionColor = texture(u_SkyBox, normalize(v_Reflection));

	gl_FragColor = mix(refractionColor, reflectionColor, v_Fresnel);
	gl_FragColor = mix(gl_FragColor, total, 0.25);
	//gl_FragColor = refractionColor;
	//gl_FragColor = reflectionColor;
	gl_FragColor.a = 1;
}