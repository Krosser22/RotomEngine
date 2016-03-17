#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;

in vec2 uvMaterial;

out vec4 fragment;

void main() {
  //Texture
  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;

  //Final
  fragment = materialColor;
};