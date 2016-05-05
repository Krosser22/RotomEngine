#version 330 core

uniform samplerCube u_skybox;

in vec3 uvMaterial;

out vec4 fragment;

void main() {
  //Final
	fragment = texture(u_skybox, uvMaterial);
};