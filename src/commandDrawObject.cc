/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "commandDrawObject.h"
#include "security.h"
#include "gl.h"

ROTOM::CommandDrawObject::CommandDrawObject() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_CommandDrawObject);

  lightPosition_[0] = 0.0f;
  lightPosition_[1] = 0.0f;
  lightPosition_[2] = 0.0f;

  lightColor_[0] = 1.0f;
  lightColor_[1] = 0.0f;
  lightColor_[2] = 1.0f;

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

ROTOM::CommandDrawObject::~CommandDrawObject() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_CommandDrawObject);
}

void ROTOM::CommandDrawObject::run() {
  for (unsigned int i = 0; i < root_->childCount(); ++i) {
    draw((Drawable *)root_->getChildAt(i));
  }
}

void ROTOM::CommandDrawObject::setRoot(Node *root) {
  root_ = root;
}

void ROTOM::CommandDrawObject::setProjectionMatrix(float *projectionMatrix) {
  projectionMatrix_ = projectionMatrix;
}

void ROTOM::CommandDrawObject::draw(Drawable *drawable) {
  std::shared_ptr<Geometry> geometry = drawable->geometry();
  std::shared_ptr<Material> material = drawable->material();
  const float *color = material->color();
  const unsigned int program = material->shaderProgram();
  glUseProgram(program);

  //Texture
  glBindTexture(GL_TEXTURE_2D, (material->texture()));
  
  // Get their uniform location
  GLint u_color = glGetUniformLocation(program, "u_color");
  GLint u_model = glGetUniformLocation(program, "u_model");
  GLint u_view = glGetUniformLocation(program, "u_view");
  GLint u_projection = glGetUniformLocation(program, "u_projection");
  GLint u_lightPosition = glGetUniformLocation(program, "u_lightPosition");
  GLint u_lightColor = glGetUniformLocation(program, "u_lightColor");
  GLint u_texture = glGetUniformLocation(program, "u_texture");
  GLint u_shininess = glGetUniformLocation(program, "u_shininess");
  GLint u_specularIntensity = glGetUniformLocation(program, "u_specularIntensity");
  GLint u_specularMaterial = glGetUniformLocation(program, "u_specularMaterial");

  //TODO - Change this hardcode variable
  //GLfloat lightPosition_[3] = { 500.0f, 500.0f, 500.0f };
  //GLfloat lightColor_[3] = { 1.0f, 0.0f, 1.0f };
  //GLfloat shininess_ = 500.0f;
  //GLfloat specularIntensity_[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  //GLfloat specularMaterial_[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

  // Pass them to the shaders
  float *f_model = glm::value_ptr(drawable->modelLocal()[0]);
  float *f_view = glm::value_ptr(drawable->modelWorld()[0]);
  //glm::mat4 temp = glm::mat4();
  //float *f_view = glm::value_ptr(temp);
  glUniformMatrix4fv(u_model, 1, GL_FALSE, f_model);
  glUniformMatrix4fv(u_view, 1, GL_FALSE, f_view);
  glUniformMatrix4fv(u_projection, 1, GL_FALSE, projectionMatrix_);
  glUniform3f(u_lightPosition, lightPosition_[0], lightPosition_[1], lightPosition_[2]);

  //glUniform4f(u_color, color[0], color[1], color[2], color[3]);
  glUniform3f(u_lightColor, lightColor_[0], lightColor_[1], lightColor_[2]);
  glUniform1f(u_shininess, shininess_);
  glUniform4f(u_specularIntensity, specularIntensity_[0], specularIntensity_[1], specularIntensity_[2], specularIntensity_[3]);
  glUniform4f(u_specularMaterial, specularMaterial_[0], specularMaterial_[1], specularMaterial_[2], specularMaterial_[3]);

  glBindVertexArray(geometry->VAO());
  glDrawElements(GL_TRIANGLES, geometry->vertexCount(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  drawChilds(drawable);
}

void ROTOM::CommandDrawObject::drawChilds(Drawable *drawable) {
  for (unsigned int i = 0; i < drawable->childCount(); ++i) {
    draw((Drawable *)drawable->getChildAt(i));
  }
}