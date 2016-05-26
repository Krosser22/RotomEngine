#version 330 core

#define MAX_LIGHTS 10
uniform int u_spotLightsCount;
uniform struct Light {
  vec4 position;
  vec3 color;
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

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    if(light.position.w == 0.0) {
        //directional light
        surfaceToLight = normalize(light.position.xyz);
        attenuation = 1.0; //no attenuation for directional lights
    } else {
        //point light
        surfaceToLight = normalize(light.position.xyz - surfacePos);
        float distanceToLight = length(light.position.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

        //cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
        if(lightToSurfaceAngle > light.coneAngle){
            attenuation = 0.0;
        }
    }

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.color;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.color;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), u_shininess);
    vec3 specular = specularCoefficient * u_specularMaterial * light.color;

    //linear color (color before gamma correction)
    return ambient + attenuation*(diffuse + specular);
}

void main() {
  vec3 normal = normalize(normalDirection);
  vec4 surfaceColor = texture(u_texture, uvMaterial);
  vec3 surfaceToCamera = normalize(u_viewPosition - fragmentPosition);

  //combine color from all the lights
  vec3 linearColor = vec3(0);
  for(int i = 0; i < u_spotLightsCount; ++i){
    linearColor += ApplyLight(u_allLights[i], surfaceColor.rgb, normal, fragmentPosition, surfaceToCamera);
  }
    
  //final color (after gamma correction)
  vec3 gamma = vec3(1.0/2.2);
  fragment = vec4(pow(linearColor, gamma), surfaceColor.a);
}