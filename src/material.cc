/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "material.h"

#include "gl.h"
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
"  finalColor.x = 1.0 - finalColor.x;\n"
"  finalColor.y = 1.0 - finalColor.y;\n"
"  finalColor.z = 1.0 - finalColor.z;\n"
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
"  fragment = vec4(texture(u_texture, uvMaterial).xyz * cosAngleSpecular, 1.0);\n"
////////////////////////////////////////////

"};\0";

ROTOM::Material::Material() {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Material);

  setColor(1.0f, 1.0f, 1.0f, 1.0f);
  setTexture("../../../../img/texture.png"); //TODO - change this path XD
  setShader(vertexShaderSource_, fragmentShaderSource_);
}

ROTOM::Material::Material(const char *texturePath) {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Material);

  setColor(1.0f, 1.0f, 1.0f, 1.0f);
  setTexture(texturePath);
  setShader(vertexShaderSource_, fragmentShaderSource_);
}

ROTOM::Material::~Material() {
  ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Material);

  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteProgram(shaderProgram_);
}

void ROTOM::Material::setShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
  GLint success;
  GLchar infoLog[512];

  // Vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);// Check for compile time errors
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);// Check for compile time errors
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Link shaders
  shaderProgram_ = glCreateProgram();
  glAttachShader(shaderProgram_, vertexShader);
  glAttachShader(shaderProgram_, fragmentShader);
  glLinkProgram(shaderProgram_);
  glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);// Check for linking errors
  if (!success) {
    glGetProgramInfoLog(shaderProgram_, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
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
  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

  // Set the texture wrapping/filtering options (on the currently bound texture object)
  // Set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load and generate the texture
  // Load image, create texture and generate mipmaps
  //FILE *file = fopen(texturePath, "r");
  //if (file == NULL) printf("ERROR AL ABRIR %s\n", texturePath);
  //float *image = stbi_loadf_from_file(file, &textureWidth_, &textureHeight_, 0, 0);
  unsigned char *image = SOIL_load_image(texturePath, &textureWidth_, &textureHeight_, 0, SOIL_LOAD_RGB); //Line 1425 of SOIL.c
  if (image == NULL) printf("ERROR AL ABRIR: [%s]\n", texturePath);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth_, textureHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void ROTOM::Material::textureSize(int &width, int &height) {
  width = textureWidth_;
  height = textureHeight_;
}

const unsigned int ROTOM::Material::texture() {
  return texture_;
}

const unsigned int ROTOM::Material::shaderProgram() {
  return shaderProgram_;
}