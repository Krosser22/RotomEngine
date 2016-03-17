#version 330 core

uniform vec4 u_color;

out vec4 fragment;

void main() {
	fragment = u_color;
};