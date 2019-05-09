#version 330 core

in vec3 v_Position;
in vec2 v_TexCoords;
in vec3 v_Normal;
in float v_Visibility;

// Camera
uniform vec3 u_CamPosition;

// Light
uniform vec3 u_I; // intensity
uniform vec3 u_LightPosition;
uniform vec3 u_Ia; // ambient color

// Texture
uniform sampler2D u_BackgroundTexture;
uniform sampler2D u_RTexture;
uniform sampler2D u_GTexture;
uniform sampler2D u_BTexture;
uniform sampler2D u_BlendMap;
uniform float u_ka; // ambient reflection constant
uniform float u_kd; // diffuse reflection constant
uniform float u_ks; // specular reflection constant
uniform float u_p; // shininess constant

uniform vec3 u_SkyColor;

void main(void) {
	vec4 blendMapColor = texture(u_BlendMap, v_TexCoords);
	float backgroundTextureWeight = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = v_TexCoords * 40;
	vec4 backgroundTextureColor = texture(u_BackgroundTexture, tiledCoords) * backgroundTextureWeight;
	vec4 rTextureColor = texture(u_RTexture, tiledCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(u_GTexture, tiledCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(u_BTexture, tiledCoords) * blendMapColor.b;
	vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;

	vec3 n = normalize(v_Normal);
	vec3 l = normalize(u_LightPosition - v_Position); // to light
	vec3 v = normalize(u_CamPosition - v_Position); // to camera
	vec3 h = (v + l) / length(v + l); // bisector of l and v

	vec3 I_falloff = u_I / pow(length(u_LightPosition - v_Position), 2); // intensity falls off as squared distance

	vec3 ambient = u_ka * u_Ia;
	vec3 diffuse = u_kd * I_falloff * max(dot(n, l), 0);
	vec3 specular = u_ks * I_falloff * pow(max(dot(n, h), 0), u_p);

	gl_FragColor = (vec4(ambient, 1.0) + vec4(diffuse, 1.0)) * totalColor + vec4(specular, 1.0);
	gl_FragColor.a = 1; // just in case u_ka, u_kd, u_ks scale alpha in above calculations
	//gl_FragColor = mix(vec4(u_SkyColor, 1), gl_FragColor, v_Visibility);
}