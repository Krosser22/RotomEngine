#version 330 core

uniform vec4 u_color;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;
uniform sampler2D u_texture;
uniform float u_shininess;
uniform vec3 u_specularIntensity;
uniform vec3 u_specularMaterial;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 lightDirection;
in vec3 worldPosition;
in vec3 cameraPosition;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;

  //Normalize on every fragment
  vec3 lightDirectionNormalized = normalize(lightDirection);
  vec3 normalDirectionNormalized = normalize(normalDirection);

  //Ambient Light
  vec3 ambient = u_lightColor * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = u_lightColor * max(dot(normalDirectionNormalized, lightDirectionNormalized), 0.0f);

  //Specular Light
  //vec3 viewDirection = normalize(cameraPosition - worldPosition);
  vec3 viewDirection = normalize(normalDirection - cameraPosition);
  vec3 reflectionDirection = reflect(-lightDirectionNormalized, normalDirectionNormalized);
  float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), u_shininess);
  vec3 specular = u_lightColor * spec * u_specularIntensity * u_specularMaterial;

  //Final
  fragment = materialColor * vec4((ambient + diffuse + specular), 1.0f);
};
