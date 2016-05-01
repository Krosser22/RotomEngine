#version 330 core

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform vec3 u_lightPosition;
uniform float u_ambientStrength;
uniform vec3 u_lightColor;
uniform float u_shininess;
uniform vec3 u_specularIntensity;
uniform vec3 u_specularMaterial;
uniform vec3 u_viewPosition;
uniform sampler2D u_depthMap;

in vec3 fragmentPosition;
in vec3 normalDirection;
in vec2 uvMaterial;
in vec4 lightFragmentPosition;

out vec4 fragment;

float ShadowCalculation(vec4 fragPosLightSpace) {
  //Perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

  //Transform to [0,1] range
  projCoords = projCoords * 0.5f + 0.5f;

  //Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(u_depthMap, projCoords.xy).r; 

  //Get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;

  //Check whether current frag pos is in shadow
  float shadow = currentDepth > closestDepth ? 1.0f : 0.0f;

  return shadow;
}

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
  
  //Blinn-Phong Specular Light
  vec3 viewDirectionNormalized = normalize(u_viewPosition - fragmentPosition);
  vec3 halfwayDir = normalize(lightDirectionNormalized + viewDirectionNormalized);  
  float spec = pow(max(dot(normalDirectionNormalized, halfwayDir), 0.0f), u_shininess);
  vec3 specular = u_lightColor * spec * u_specularIntensity * u_specularMaterial;
  
  //Shadow
  float shadow = ShadowCalculation(lightFragmentPosition);

  //Final
  fragment = materialColor * vec4((ambient + (1.0f - shadow) * (diffuse + specular)), 1.0f);
};