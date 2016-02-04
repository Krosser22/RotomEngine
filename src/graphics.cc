#include "graphics.h"

void ROTOM::GRAPHICS::setShader(ShaderData *shaderData, const char *vertexShaderSource, const char *fragmentShaderSource) {
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
  shaderData->shaderProgram = glCreateProgram();
  glAttachShader(shaderData->shaderProgram, vertexShader);
  glAttachShader(shaderData->shaderProgram, fragmentShader);
  glLinkProgram(shaderData->shaderProgram);
  glGetProgramiv(shaderData->shaderProgram, GL_LINK_STATUS, &success);// Check for linking errors
  if (!success) {
    glGetProgramInfoLog(shaderData->shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(shaderData->shaderProgram);

  // Get their uniform location
  shaderData->u_color = glGetUniformLocation(shaderData->shaderProgram, "u_color");
  shaderData->u_model = glGetUniformLocation(shaderData->shaderProgram, "u_model");
  shaderData->u_view = glGetUniformLocation(shaderData->shaderProgram, "u_view");
  shaderData->u_projection = glGetUniformLocation(shaderData->shaderProgram, "u_projection");
  shaderData->u_lightPosition = glGetUniformLocation(shaderData->shaderProgram, "u_lightPosition");
  shaderData->u_lightColor = glGetUniformLocation(shaderData->shaderProgram, "u_lightColor");
  shaderData->u_texture = glGetUniformLocation(shaderData->shaderProgram, "u_texture");
  shaderData->u_shininess = glGetUniformLocation(shaderData->shaderProgram, "u_shininess");
  shaderData->u_specularIntensity = glGetUniformLocation(shaderData->shaderProgram, "u_specularIntensity");
  shaderData->u_specularMaterial = glGetUniformLocation(shaderData->shaderProgram, "u_specularMaterial");
}

void ROTOM::GRAPHICS::useMaterial(ShaderData *shaderData, Drawable *drawable, float *projectionMatrix) {
  //printf("%f - %f - %f\n", generalData.lightPositionX, generalData.lightPositionY, generalData.lightPositionZ);
  float *f_model = glm::value_ptr(drawable->modelLocal()[0]);
  float *f_view = glm::value_ptr(drawable->modelWorld()[0]); //TODO - Use the real view
  float lightPosition[3] = { drawable->material()->generalShaderData_->lightPositionX, drawable->material()->generalShaderData_->lightPositionY, drawable->material()->generalShaderData_->lightPositionZ };
  float lightColor[3] = { drawable->material()->generalShaderData_->lightColorX, drawable->material()->generalShaderData_->lightColorY, drawable->material()->generalShaderData_->lightColorZ };
  //const float *color = drawable->material()->color();
  const float shininess = drawable->material()->shininess_;
  const float *specularIntensity = drawable->material()->specularIntensity_;
  const float *specularMaterial = drawable->material()->specularMaterial_;

  glUseProgram(shaderData->shaderProgram);

  //Texture
  glBindTexture(GL_TEXTURE_2D, drawable->material()->texture());

  // Pass them to the shaders
  glUniformMatrix4fv(shaderData->u_model, 1, GL_FALSE, f_model);
  glUniformMatrix4fv(shaderData->u_view, 1, GL_FALSE, f_view);
  glUniformMatrix4fv(shaderData->u_projection, 1, GL_FALSE, projectionMatrix);
  glUniform3f(shaderData->u_lightPosition, lightPosition[0], lightPosition[1], lightPosition[2]);
  //glUniform4f(u_color, color[0], color[1], color[2], color[3]);
  glUniform3f(shaderData->u_lightColor, lightColor[0], lightColor[1], lightColor[2]);
  glUniform1f(shaderData->u_shininess, shininess);
  glUniform4f(shaderData->u_specularIntensity, specularIntensity[0], specularIntensity[1], specularIntensity[2], specularIntensity[3]);
  glUniform4f(shaderData->u_specularMaterial, specularMaterial[0], specularMaterial[1], specularMaterial[2], specularMaterial[3]);

  glBindVertexArray(drawable->geometry()->VAO());
  glDrawElements(GL_TRIANGLES, drawable->geometry()->vertexCount(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}