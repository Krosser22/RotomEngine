#version 330 core

uniform sampler2D u_colorMap;
uniform float u_exposure;

in vec2 TexCoords;

out vec4 fragment;

void main() {
  const float gamma = 2.2f;
  vec3 hdrColor = texture(u_colorMap, TexCoords).rgb;
  
  //Exposure tone mapping
  vec3 mapped = vec3(1.0f) - exp(-hdrColor * u_exposure);

  //Gamma correction
  mapped = pow(mapped, vec3(1.0f / gamma));
  
  fragment = vec4(mapped, 1.0f);
}