#version 330 core

uniform vec3 u_viewPosition;
uniform samplerCube u_skybox;

in vec3 Normal;
in vec3 Position;

out vec4 fragment;

void main() {
  vec3 I = normalize(Position - u_viewPosition);
  vec3 R = reflect(I, normalize(Normal));

  //Final
	fragment = texture(u_skybox, R);
}