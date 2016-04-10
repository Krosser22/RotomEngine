#version 330 core

uniform vec4 u_color;
uniform vec3 u_lightColor;
uniform float u_ambientStrength;
uniform sampler2D u_texture;

in vec3 normalDirection;
in vec2 uvMaterial;
in vec3 lightDirection;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;

  //Ambient Light
  vec3 ambient = u_lightColor * u_ambientStrength;

  //Diffuse Light
  vec3 diffuse = u_lightColor * max(dot(normalize(normalDirection), normalize(lightDirection)), 0.0f);

  //Final
  fragment = materialColor * vec4((ambient + diffuse), 1.0f);
};