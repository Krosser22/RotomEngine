/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "drawable.h"
#include "security.h"
#include "graphics.h"

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

ROTOM::Drawable::Drawable() {
  SECURITY::addSecurityCount(SECURITY::MyClass_Drawable);

  geometry_ = NULL;
  material_ = NULL;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings));
  setColor(1.0f, 1.0f, 1.0f, 1.0f);
  material_->setShader(materialSettings_.get(), vertexShaderSource_, fragmentShaderSource_);
}

ROTOM::Drawable::Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, Node *parent) {
  SECURITY::addSecurityCount(SECURITY::MyClass_Drawable);

  setGeometry(geometry);
  setMaterial(material);
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings));
  setParent(parent);
}

ROTOM::Drawable::~Drawable() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_Drawable);

  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseMaterial(materialSettings_->shaderProgram);
}

void ROTOM::Drawable::setGeometry(std::shared_ptr<Geometry> geometry) {
  geometry_ = geometry;
}

std::shared_ptr<ROTOM::Geometry> ROTOM::Drawable::geometry() {
  return geometry_;
}

void ROTOM::Drawable::setMaterial(std::shared_ptr<Material> material) {
  material_ = material;
}

std::shared_ptr<ROTOM::Material> ROTOM::Drawable::material() {
  return material_;
}

void ROTOM::Drawable::setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings) {
  materialSettings_ = materialSettings;
}

std::shared_ptr<ROTOM::MaterialSettings> ROTOM::Drawable::materialSettings() {
  return materialSettings_;
}

void ROTOM::Drawable::setColor(const float r, const float g, const float b, const float a) {
  color_[0] = r;
  color_[1] = g;
  color_[2] = b;
  color_[3] = a;
}

const float *ROTOM::Drawable::color() {
  return color_;
}