#version 330 core

uniform sampler2D u_texture;

in vec2 uvMaterial;

out vec4 fragment;

void main() {
	fragment = texture(u_texture, uvMaterial);
	//fragment = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};