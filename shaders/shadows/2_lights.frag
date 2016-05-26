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
      shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;     
    }
  }
  shadow /= 9.0f;

  // Keep the shadow at 0.0f when outside the far_plane region of the light's frustum.
  if(projCoords.z > 1.0f) {
    shadow = 0.0f;
  }

  return shadow;
}

vec3 ApplyLight (Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
  vec3 surfaceToLight;
  float attenuation = 1.0f;
  if (light.position.w == 0.0f) {
    //directional light
    surfaceToLight = normalize(light.position.xyz);
    attenuation = 1.0f; //no attenuation for directional lights
  } else {
    //point light
    surfaceToLight = normalize(light.position.xyz - surfacePos);
    float distanceToLight = length(light.position.xyz - surfacePos);
    attenuation = 1.0f / (1.0f + light.attenuation * pow(distanceToLight, 2));

    //cone restrictions (affects attenuation)
    float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
    if (lightToSurfaceAngle > light.coneAngle) {
      attenuation = 0.0f;
    }
  }

  //ambient
  vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.color;

  //diffuse
  float diffuseCoefficient = max(0.0f, dot(normal, surfaceToLight));
  vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.color;
  
  //specular
  float specularCoefficient = 0.0f;
  if (diffuseCoefficient > 0.0f) {
    specularCoefficient = pow(max(0.0f, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), u_shininess);
  }
  vec3 specular = specularCoefficient * u_specularMaterial * light.color;

  //linear color (color before gamma correction)
  return ambient + attenuation * (diffuse + specular);
}

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial);
  
  //Normalize on every fragment
  lightDirectionNormalized = normalize(u_allLights[0].position.xyz - fragmentPosition);
  normalDirectionNormalized = normalize(normalDirection);
  vec3 surfaceToCamera = normalize(u_viewPosition - fragmentPosition);

  //combine color from all the lights
  vec3 linearColor = vec3(0.0f);
  for (int i = 0; i < u_spotLightsCount; ++i) {
    linearColor += ApplyLight(u_allLights[i], materialColor.rgb, normalDirectionNormalized, fragmentPosition, surfaceToCamera);
  }

  //final color (after gamma correction)
  vec3 gamma = vec3(1.0f / 2.2f);
  fragment = vec4(pow(linearColor, gamma), materialColor.a);

  //Ambient Light
  vec3 ambient = linearColor * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = linearColor * max(dot(lightDirectionNormalized, normalDirectionNormalized), 0.0f);
  
  //Blinn-Phong Specular Light
  vec3 viewDirectionNormalized = normalize(u_viewPosition - fragmentPosition);
  vec3 halfwayDir = normalize(lightDirectionNormalized + viewDirectionNormalized);  
  float spec = pow(max(dot(normalDirectionNormalized, halfwayDir), 0.0f), u_shininess);
  vec3 specular = linearColor * spec * u_specularIntensity * u_specularMaterial;
  
  //Shadow
  float shadow = u_shadows ? ShadowCalculation(lightFragmentPosition) : 0.0f;
  shadow = min(shadow, 0.75f); // reduce shadow strength a little: allow some diffuse/specular light in shadowed regions
  
  //Final
  fragment *= vec4((ambient + (1.0f - shadow) * (diffuse + specular)), 1.0f);
}