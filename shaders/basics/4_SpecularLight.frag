#version 330 core

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform vec3 u_lightPosition;
uniform float u_ambientStrength;
uniform vec3 u_lightColor;
uniform float u_shininess;
uniform vec3 u_specularIntensity;
uniform vec3 u_specularMaterial;
uniform vec3 u_viewDirection;

in vec3 fragmentPosition;
in vec3 normalDirection;
in vec2 uvMaterial;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;
  
  //Normalize on every fragment
  vec3 lightDirectionNormalized = normalize(u_lightPosition - fragmentPosition);
  vec3 normalDirectionNormalized = normalize(normalDirection);

  //Ambient Light
  vec3 ambient = u_lightColor * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = u_lightColor * max(dot(lightDirectionNormalized, normalDirectionNormalized), 0.0f);

  //Specular Light
  vec3 viewDirectionNormalized = normalize(u_viewDirection - fragmentPosition);
  vec3 reflectionDirection = reflect(-lightDirectionNormalized, normalDirectionNormalized);
  float spec = pow(max(dot(viewDirectionNormalized, reflectionDirection), 0.0f), u_shininess);
  vec3 specular = u_lightColor * spec * u_specularIntensity * u_specularMaterial;

  //Final
  fragment = materialColor * vec4((ambient + diffuse + specular), 1.0f);
  //fragment = vec4(1.0f, 1.0f, 0.0f, 1.0f);
};