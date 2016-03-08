#version 330 core

uniform vec4 u_color;
uniform vec3 u_lightPosition;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;
uniform mat4 u_view;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 worldPosition;

out vec4 fragment;

void main() {
	//Light
	//vec4 lightPosition = u_view * vec4(u_lightPosition, 1.0f);
	vec3 lightDirection = normalize(u_lightPosition - worldPosition);

    //Ambient Light
    vec3 ambient = u_lightColor * u_ambientStrength;

	//Diffuse Light
    float diff = max(dot(normalize(normalDirection), lightDirection), 0.0f);
    vec3 diffuse = u_lightColor * diff;

    vec3 finalColor = u_color.xyz * (ambient + diffuse);

	fragment = vec4(finalColor, 1.0f);
};