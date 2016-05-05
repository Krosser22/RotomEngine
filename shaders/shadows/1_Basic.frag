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
uniform bool u_shadows;

in vec3 fragmentPosition;
in vec3 normalDirection;
in vec2 uvMaterial;
in vec4 lightFragmentPosition;

out vec4 fragment;

vec3 lightDirectionNormalized;
vec3 normalDirectionNormalized;

float ShadowCalculation(vec4 fragPosLightSpace) {
  //Perform perspective divide
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

  //Transform to [0,1] range
  projCoords = projCoords * 0.5f + 0.5f;

  //Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth = texture(u_depthMap, projCoords.xy).r;
  
  //Get depth of current fragment from light's perspective
  float currentDepth = projCoords.z;

  //Calculate bias (based on depth map resolution and slope)
  float bias = max(0.05f * (1.0f - dot(normalDirectionNormalized, lightDirectionNormalized)), 0.005f);
  
  //Check whether current frag pos is in shadow
  //PCF (percentage-closer filtering)
  float shadow = 0.0f;
  vec2 texelSize = 1.0f / textureSize(u_depthMap, 0);
  for(int x = -1; x <= 1; ++x) {
    for(int y = -1; y <= 1; ++y) {
      float pcfDepth = texture(u_depthMap, projCoords.xy + vec2(x, y) * texelSize).r;
      shadow += currentDepth - bias > pcfDepth  ? 1.0f : 0.0f;     
    }
  }
  shadow /= 9.0f;

  // Keep the shadow at 0.0f when outside the far_plane region of the light's frustum.
  if(projCoords.z > 1.0f) {
    shadow = 0.0f;
  }

  return shadow;
}

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;
  
  //Normalize on every fragment
  lightDirectionNormalized = normalize(u_lightPosition - fragmentPosition);
  normalDirectionNormalized = normalize(normalDirection);

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
  float shadow = u_shadows ? ShadowCalculation(lightFragmentPosition) : 0.0f;
  shadow = min(shadow, 0.75f); // reduce shadow strength a little: allow some diffuse/specular light in shadowed regions
  
  //Final
  fragment = materialColor * vec4((ambient + (1.0f - shadow) * (diffuse + specular)), 1.0f);
};