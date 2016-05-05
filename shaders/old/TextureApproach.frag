#version 330
uniform vec3 u_light_color;
uniform sampler2D u_texture_material;
uniform float u_shininess;
uniform vec3 u_specular_intensity;
uniform vec3 u_specular_material;

in vec3 light_direction;
in vec3 normal_direction;
in vec4 camera_position;
in vec2 uv_material;

out vec4 fragment;

void main() {
  float cos_angle_difuse = max(0.0, dot(normalize(light_direction), normalize(normal_direction)));
  vec4 difuse_color = vec4(texture(u_texture_material, uv_material).xyz * u_light_color * cos_angle_difuse, 1.0);
  
  vec3 view_direction = normalize(normalize(normal_direction) - camera_position.xyz);
  vec3 halfWay = normalize(normalize(light_direction) + view_direction);

  float cos_angle_specular = max(0.0, dot(halfWay, normalize(normal_direction)));
  vec4 specular_color = vec4(pow(cos_angle_specular, u_shininess) * u_specular_intensity * u_specular_material, 1.0);
  
  vec4 final_color = difuse_color + specular_color;
  final_color.w = min(1.0, final_color.w);
  
  final_color.x = 1.0 - final_color.x;
  final_color.y = 1.0 - final_color.y;
  final_color.z = 1.0 - final_color.z;
  fragment = final_color;
};