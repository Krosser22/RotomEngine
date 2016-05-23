#version 330 core

uniform vec3 u_viewPosition;
uniform samplerCube u_skybox;

in vec3 Normal;
in vec3 Position;

out vec4 fragment;

void main() {
  float ratio = 1.00 / 1.52;
  vec3 I = normalize(Position - u_viewPosition);
  vec3 R = refract(I, normalize(Normal), ratio);

  //Final
	fragment = texture(u_skybox, R);
}