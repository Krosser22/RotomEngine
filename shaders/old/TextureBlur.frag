#version 330
precision mediump float;

uniform vec3 u_light_color;
uniform sampler2D u_texture_material;
uniform float u_shininess;
uniform vec3 u_specular_intensity;
uniform vec3 u_specular_material;
uniform float u_time;

uniform float resolution;
uniform float radius;
uniform vec2 dir;

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
  final_color.w = min(1.0, final_color.w * max(0.3, sin(u_time)));
  
  vec4 sum = vec4(0.0);
  //float blur = radius/resolution; 
  float blur = sin(u_time);

  sum += texture2D(u_texture_material, vec2(uv_material.x - 4.0 * blur * sin(u_time * 0.5), uv_material.y - 4.0 * blur * cos(u_time * 0.5))) * 0.0162162162;
  sum += texture2D(u_texture_material, vec2(uv_material.x - 3.0 * blur * sin(u_time * 0.5), uv_material.y - 3.0 * blur * cos(u_time * 0.5))) * 0.0540540541;
  sum += texture2D(u_texture_material, vec2(uv_material.x - 2.0 * blur * sin(u_time * 0.5), uv_material.y - 2.0 * blur * cos(u_time * 0.5))) * 0.1216216216;
  sum += texture2D(u_texture_material, vec2(uv_material.x - 1.0 * blur * sin(u_time * 0.5), uv_material.y - 1.0 * blur * cos(u_time * 0.5))) * 0.1945945946;
  sum += texture2D(u_texture_material, vec2(uv_material.x, uv_material.y)) * 0.2270270270;
  sum += texture2D(u_texture_material, vec2(uv_material.x + 1.0 * blur * sin(u_time * 0.5), uv_material.y + 1.0 * blur * cos(u_time * 0.5))) * 0.1945945946;
  sum += texture2D(u_texture_material, vec2(uv_material.x + 2.0 * blur * sin(u_time * 0.5), uv_material.y + 2.0 * blur * cos(u_time * 0.5))) * 0.1216216216;
  sum += texture2D(u_texture_material, vec2(uv_material.x + 3.0 * blur * sin(u_time * 0.5), uv_material.y + 3.0 * blur * cos(u_time * 0.5))) * 0.0540540541;
  sum += texture2D(u_texture_material, vec2(uv_material.x + 4.0 * blur * sin(u_time * 0.5), uv_material.y + 4.0 * blur * cos(u_time * 0.5))) * 0.0162162162;

  fragment = final_color * vec4(sum.rgb, 1.0);
};