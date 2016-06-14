#version 330 core

#define MAX_LIGHTS 32
uniform int u_spotLightsCount;
uniform struct Light {
  vec4 position;
  vec3 color;
  vec3 rotation;
  float attenuation;
  float ambientCoefficient;
  float coneAngle;
  vec3 coneDirection;
} u_allLights[MAX_LIGHTS];

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_ambientStrength;

in vec3 fragmentPosition;
in vec3 normalDirection;
in vec2 uvMaterial;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;
  
  //Normalize on every fragment
  vec3 lightDirectionNormalized = normalize(u_allLights[0].position.xyz - fragmentPosition);
  vec3 normalDirectionNormalized = normalize(normalDirection);

  //Ambient Light
  vec3 ambient = u_allLights[0].color * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = u_allLights[0].color * max(dot(lightDirectionNormalized, normalDirectionNormalized), 0.0f);

  //Final
  fragment = materialColor * vec4((ambient + diffuse), 1.0f);
}