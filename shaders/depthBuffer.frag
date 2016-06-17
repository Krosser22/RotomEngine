#version 330 core

out vec4 fragment;

float near = 1.0f;
float far  = 100.0f;

float LinearizeDepth(float depth) {
	float z = depth * 2.0f - 1.0f;
	return (2.0f * near * far) / (far + near - z * (far - near));
}

void main() {
	float depth = 1.0f - LinearizeDepth(gl_FragCoord.z) / far;
	fragment = vec4(vec3(depth), 1.0f);
}