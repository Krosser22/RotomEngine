#version 330 core

uniform sampler2D u_texture;

in vec2 uvMaterial;

out vec4 fragment;

void main() {
  //Texture
  float depthValue = texture(u_texture, uvMaterial).r;

  //Final
  fragment = vec4(vec3(depthValue), 1.0f);
}