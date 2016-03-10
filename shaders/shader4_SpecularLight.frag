#version 330 core

uniform vec4 u_color;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;
uniform sampler2D u_texture;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 lightDirection;
in vec3 worldPosition;
in vec3 cameraPosition;

out vec4 fragment;

void main() {
	//Texture
	vec3 materialColor = texture(u_texture, uvMaterial).xyz * u_color.xyz;

	//Normalize
	vec3 lightDirectionNormalized = normalize(lightDirection);
	vec3 normalDirectionNormalized = normalize(normalDirection);

    //Ambient Light
    vec3 ambient = u_lightColor * u_ambientStrength;

	//Diffuse Light
    vec3 diffuse = u_lightColor * max(dot(normalDirectionNormalized, lightDirectionNormalized), 0.0f);

	//Specular Light
    float specularStrength = 5.0f;
	float shininess = 20;
	vec3 viewDirection = normalize(normalDirection - cameraPosition);
	//vec3 viewDirection = normalize(cameraPosition - worldPosition);

    vec3 reflectionDirection = reflect(-lightDirectionNormalized, normalDirectionNormalized);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);
    vec3 specular = u_lightColor * spec * specularStrength;

	//Final
	fragment = vec4(materialColor * (ambient + diffuse + specular), 1.0f);
};

//half-vector