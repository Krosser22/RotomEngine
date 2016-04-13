#version 330 core

uniform vec4 u_color;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;
uniform sampler2D u_texture;
uniform vec3 u_lightPosition;
uniform vec3 viewPosition;
uniform bool blinn;

in VS_OUT {
  vec3 worldPosition;
  vec3 normalDirection;
  vec2 uvMaterial;
} i_fragment;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, i_fragment.uvMaterial) * u_color;

  //Normalize on every fragment
  vec3 lightDirectionNormalized = normalize(u_lightPosition - i_fragment.worldPosition);
  vec3 normalDirectionNormalized = normalize(i_fragment.normalDirection);
  
  //Ambient Light
  vec3 ambient = u_lightColor * u_ambientStrength;
  
  //Diffuse Light
  vec3 diffuse = materialColor.xyz * max(dot(lightDirectionNormalized, normalDirectionNormalized), 0.0f);
  
  //Specular Light
  //vec3 viewDirection = normalize(cameraPosition - worldPosition);
  //vec3 viewDirection = normalize(normalDirection - cameraPosition);
  vec3 viewDirection = normalize(viewPosition - i_fragment.worldPosition);
  //vec3 reflectionDirection = reflect(-lightDirectionNormalized, normalDirectionNormalized);
  //float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0f), u_shininess);
  float spec = 0.0f;
  //vec3 specular = u_lightColor * spec * u_specularIntensity * u_specularMaterial;
  if(blinn) {
    vec3 halfwayDir = normalize(lightDirectionNormalized + viewDirection);  
    spec = pow(max(dot(normalDirectionNormalized, halfwayDir), 0.0f), 32.0f);
  } else {
    vec3 reflectionDirection = reflect(-lightDirectionNormalized, normalDirectionNormalized);
    spec = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
  }
  vec3 specular = vec3(0.3f) * spec; // assuming bright white light color
  fragment = vec4(ambient + diffuse + specular, 1.0f);
  
  //Final
  //fragment = materialColor * vec4((ambient + diffuse + specular), 1.0f);
}



/*#version 330 core

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
};*/