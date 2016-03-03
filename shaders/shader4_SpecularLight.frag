#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform vec3 u_lightColor;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 lightDirection;
in vec3 cameraPosition;

out vec4 fragment;

void main() {
	//Material Color
	vec3 materialColor = texture(u_texture, uvMaterial).xyz * u_color.xyz;

    //Ambient Light
    float ambientStrength = 0.05f;
    vec3 ambient = u_lightColor * ambientStrength;

	//Diffuse Light
    float diff = max(dot(normalDirection, lightDirection), 0.0);
    vec3 diffuse = diff * u_lightColor;

	//Specular Light
    float specularStrength = 5.0f;
	float shininess = 500;
	vec3 viewDirection = normalize(normalDirection - cameraPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normalDirection);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);
    vec3 specular = u_lightColor * spec * specularStrength;

    vec3 finalColor = materialColor * (ambient + diffuse + specular);

	fragment = vec4(finalColor, 1.0);
};