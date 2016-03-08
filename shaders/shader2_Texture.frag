#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;

in vec2 uvMaterial;

out vec4 fragment;

void main() {
	fragment = vec4(texture(u_texture, uvMaterial).xyz * u_color.xyz, 1.0f);
};