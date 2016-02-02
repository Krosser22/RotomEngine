#version 330
uniform vec3 u_difuse_light_color;
uniform vec3 u_difuse_material_color;
uniform float u_shininess;
uniform vec4 u_specular_intensity;
uniform vec4 u_specular_material;

in vec4 light_direction;
in vec4 normal_direction;
in vec4 camera_position;
in vec4 material_position;

float cos_angle_difuse;
float cos_angle_specular;
vec4 difuse_color;
vec4 halfWay;
vec4 view;
vec4 specular_color;

out vec4 fragment;

void main() {
  cos_angle_difuse = max(0.0, dot(light_direction.xyz, normal_direction.xyz));
  difuse_color = vec4((u_difuse_material_color + u_difuse_light_color) * cos_angle_difuse, 1.0);
  
  view = normalize(material_position - camera_position);
  halfWay = normalize(light_direction + view);

  cos_angle_specular = max(0.0, dot(halfWay, normal_direction));
  specular_color = vec4(pow(cos_angle_specular, u_shininess) * u_specular_intensity.xyz * u_specular_material.xyz, 1.0);

  fragment = difuse_color + specular_color;
};