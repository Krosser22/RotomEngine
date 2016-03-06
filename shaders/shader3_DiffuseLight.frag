#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 lightDirection;

out vec4 fragment;

void main() {
	//Material Color
	vec3 materialColor = texture(u_texture, uvMaterial).xyz * u_color.xyz;

    //Ambient Light
    vec3 ambient = u_lightColor * u_ambientStrength;

	//Diffuse Light
    float diff = max(dot(normalDirection, lightDirection), 0.0);
    vec3 diffuse = diff * u_lightColor;

    vec3 finalColor = materialColor * (ambient + diffuse);

	fragment = vec4(finalColor, 1.0);
};