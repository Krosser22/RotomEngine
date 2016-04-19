#version 330 core

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform vec3 u_lightPosition;
uniform float u_ambientStrength;
uniform vec3 u_lightColor;
uniform float u_shininess;
uniform vec3 u_specularIntensity;
uniform vec3 u_specularMaterial;
uniform vec3 u_eyePosition;

in vec3 worldPosition;
in vec3 normalDirection;
in vec2 uvMaterial;
in vec4 FragPosLightSpace;

out vec4 fragment;

float ShadowCalculation(vec4 fragPosLightSpace) {
  return 1.0f;
}

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;
  
  //Normalize on every fragment
  vec3 lightDirectionNormalized = normalize(u_lightPosition - worldPosition);
  vec3 normalDirectionNormalized = normalize(normalDirection);

  //Ambient Light
  vec3 ambient = u_lightColor * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = u_lightColor * max(dot(normalDirectionNormalized, lightDirectionNormalized), 0.0f);
  
  //Blinn-Phong Specular Light
  vec3 viewDirectionNormalized = normalize(u_eyePosition - worldPosition);
  vec3 halfwayDir = normalize(lightDirectionNormalized + viewDirectionNormalized);  
  float spec = pow(max(dot(normalDirectionNormalized, halfwayDir), 0.0f), u_shininess);
  vec3 specular = u_lightColor * spec * u_specularIntensity * u_specularMaterial;
  
  //Shadow
  float shadow = ShadowCalculation(FragPosLightSpace);

  //Final
//fragment = materialColor * vec4((ambient +                   (diffuse + specular)), 1.0f);
  fragment = materialColor * vec4((ambient + (1.0f - shadow) * (diffuse + specular)), 1.0f);
};