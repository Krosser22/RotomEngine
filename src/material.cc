/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "material.h"

#include "graphics.h"
#include "security.h"
#include "soil.h"

// Default Shaders
/*const char* vertexShaderSource_ = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 normal;\n"
"layout (location = 2) in vec2 uv;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_projection;\n"
"out vec2 uv_texture;\n"
"out vec3 normals;\n"
"void main()\n"
"{\n"
"gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);\n"
"uv_texture = uv;\n"
"normals = normalize(u_view * u_model * vec4(normal, 1.0f)).xyz;\n"
"}\0";*/

const char* vertexShaderSource_ = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec2 uv;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_projection;\n"
"uniform vec3 u_lightPosition;\n"
"out vec3 lightDirection;\n"
"out vec3 normalDirection;\n"
"out vec4 cameraPosition;\n"
"out vec4 materialPosition;\n"
"out vec2 uvMaterial;\n"
"void main() {\n"
"  mat4 mv_matrix = u_view * u_model;\n"
"  cameraPosition = u_view[3];\n"
"  //Light\n"
"  lightDirection = normalize(u_view * vec4(u_lightPosition, 1.0f) - mv_matrix * vec4(position, 1.0f)).xyz;\n"
"  normalDirection = normalize(mv_matrix * vec4(normal, 0.0f)).xyz;\n"
"  //Material\n"
"  uvMaterial = uv;\n"
"  gl_Position = u_projection * mv_matrix * vec4(position, 1.0);\n"
"};\0";

/*const char* fragmentShaderSource_ = "#version 330 core\n"
"uniform vec4 u_color;\n"
"uniform sampler2D u_texture;\n"
"in vec2 uv_texture;\n"
"in vec3 normals;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = texture(u_texture, uv_texture) * u_color;\n"
//"color = vec4(normals,1.0f);\n"
"}\n\0";*/

const char* fragmentShaderSource_ = "#version 330\n"
//"uniform vec4 u_color;\n"
"uniform sampler2D u_texture;\n"
"uniform vec3 u_lightColor;\n"
"uniform float u_shininess;\n"
"uniform vec3 u_specularIntensity;\n"
"uniform vec3 u_specularMaterial;\n"
"in vec3 lightDirection;\n"
"in vec3 normalDirection;\n"
"in vec4 cameraPosition;\n"
"in vec2 uvMaterial;\n"
"out vec4 fragment;\n"
"void main() {\n"
"  float cosAngleDifuse = max(0.0, dot(normalize(lightDirection), normalize(normalDirection)));\n"
"  vec4 difuseColor = vec4(texture(u_texture, uvMaterial).xyz * u_lightColor * cosAngleDifuse, 1.0);\n"
"  vec3 viewDirection = normalize(normalize(normalDirection) - cameraPosition.xyz);\n"
"  vec3 halfWay = normalize(normalize(lightDirection) + viewDirection);\n"
"  float cosAngleSpecular = max(0.0, dot(halfWay, normalize(normalDirection)));\n"
"  vec4 specularColor = vec4(pow(cosAngleSpecular, u_shininess) * u_specularIntensity * u_specularMaterial, 1.0);\n"
"  vec4 finalColor = difuseColor + specularColor;\n"
"  finalColor.w = min(1.0, finalColor.w);\n"
//"  finalColor.x = 1.0 - finalColor.x;\n"
//"  finalColor.y = 1.0 - finalColor.y;\n"
//"  finalColor.z = 1.0 - finalColor.z;\n"
"  fragment = finalColor;\n"

////////////////////////////////////////////
//TODO - TESTING!!!!!!!!
//"  fragment = difuseColor;\n"
//"  fragment = specularColor;\n"
//"  fragment = vec4(u_lightColor * cosAngleDifuse, 1.0);\n"
//"  fragment = vec4(normalize(lightDirection), 1.0);\n"
//"  fragment = vec4(halfWay, 1.0);\n"
//"  fragment = vec4(cosAngleDifuse, cosAngleDifuse, cosAngleDifuse, 1.0);\n"
//"  fragment = vec4(cosAngleSpecular, cosAngleSpecular, cosAngleSpecular, 1.0);\n"
//"  fragment = vec4(texture(u_texture, uvMaterial).xyz * cosAngleSpecular, 1.0);\n"
////////////////////////////////////////////
"};\0";

ROTOM::Material::Material(const char *texturePath) {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Material);
  setColor(1.0f, 1.0f, 1.0f, 1.0f);
  setTexture(texturePath);
  setShader(vertexShaderSource_, fragmentShaderSource_);

  shininess_ = 500.0f;

  specularIntensity_[0] = 0.0f;
  specularIntensity_[1] = 0.0f;
  specularIntensity_[2] = 0.0f;
  specularIntensity_[3] = 0.0f;

  specularMaterial_[0] = 0.0f;
  specularMaterial_[1] = 0.0f;
  specularMaterial_[2] = 0.0f;
  specularMaterial_[3] = 0.0f;
}

ROTOM::Material::~Material() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_Material);

  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseMaterial(shaderData_.shaderProgram);
}

void ROTOM::Material::setShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
  GRAPHICS::setShader(&shaderData_, vertexShaderSource, fragmentShaderSource);
}

void ROTOM::Material::setColor(const float r, const float g, const float b, const float a) {
  color_[0] = r;
  color_[1] = g;
  color_[2] = b;
  color_[3] = a;
}

const float *ROTOM::Material::color() {
  return color_;
}

void ROTOM::Material::setTexture(const char *texturePath) {
  // Load and generate the texture
  // Load image, create texture and generate mipmaps
  //FILE *file = fopen(texturePath, "r");
  //if (file == NULL) printf("ERROR AL ABRIR %s\n", texturePath);
  //float *image = stbi_loadf_from_file(file, &textureWidth_, &textureHeight_, 0, 0);
  unsigned char *image = SOIL_load_image(texturePath, &textureWidth_, &textureHeight_, 0, SOIL_LOAD_RGB); //Line 1425 of SOIL.c
  if (image == NULL) printf("ERROR AL ABRIR: [%s]\n", texturePath);
  GRAPHICS::setTexture(&texture_, image, &textureWidth_, &textureHeight_);
  SOIL_free_image_data(image);
}

void ROTOM::Material::textureSize(int &width, int &height) {
  width = textureWidth_;
  height = textureHeight_;
}

const unsigned int ROTOM::Material::texture() {
  return texture_;
}

const unsigned int ROTOM::Material::shaderProgram() {
  return shaderData_.shaderProgram;
}