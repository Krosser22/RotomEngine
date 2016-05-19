#version 330 core

uniform sampler2D u_texture;
uniform float u_nearPlane;
uniform float u_farPlane;

in vec2 uvMaterial;

out vec4 fragment;

float LinearizeDepth(float depth) {
    float z = depth * 2.0f - 1.0f; //Back to NDC
    return (2.0f * u_nearPlane * u_farPlane) / (u_farPlane + u_nearPlane - z * (u_farPlane - u_nearPlane));
}

void main() {
  //Texture
  float depthValue = texture(u_texture, uvMaterial).r;

  //Final
  fragment = vec4(vec3(LinearizeDepth(depthValue) / u_farPlane), 1.0f); //Perspective
  //fragment = vec4(depthValue, depthValue, depthValue, 1.0f); //Orthographic
}