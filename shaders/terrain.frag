#version 330 core

in vec4 posModel;

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
  fragment.g = (posModel.y + 1.f) / fragment.r * 1;
  fragment.r = 0.0f;
  float temp = fragment.b;
  fragment = normalize(fragment);
  fragment.a = 1.0f;
  //fragment.r = temp * 0.7f;
}