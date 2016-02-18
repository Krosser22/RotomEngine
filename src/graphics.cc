#include "graphics.h"

float ROTOM::GRAPHICS::getTime() {
  return (float)glfwGetTime();
}

void ROTOM::GRAPHICS::setShader(MaterialSettings *materialSettings, const char *vertexShaderSource, const char *fragmentShaderSource) {
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
  materialSettings->shaderProgram = glCreateProgram();
  glAttachShader(materialSettings->shaderProgram, vertexShader);
  glAttachShader(materialSettings->shaderProgram, fragmentShader);
  glLinkProgram(materialSettings->shaderProgram);
  glGetProgramiv(materialSettings->shaderProgram, GL_LINK_STATUS, &success);// Check for linking errors
  if (!success) {
    glGetProgramInfoLog(materialSettings->shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(materialSettings->shaderProgram);

  // Get their uniform location
  materialSettings->u_color = glGetUniformLocation(materialSettings->shaderProgram, "u_color");
  materialSettings->u_model = glGetUniformLocation(materialSettings->shaderProgram, "u_model");
  materialSettings->u_view = glGetUniformLocation(materialSettings->shaderProgram, "u_view");
  materialSettings->u_projection = glGetUniformLocation(materialSettings->shaderProgram, "u_projection");
  materialSettings->u_lightPosition = glGetUniformLocation(materialSettings->shaderProgram, "u_lightPosition");
  materialSettings->u_lightColor = glGetUniformLocation(materialSettings->shaderProgram, "u_lightColor");
  materialSettings->u_texture = glGetUniformLocation(materialSettings->shaderProgram, "u_texture");
  materialSettings->u_shininess = glGetUniformLocation(materialSettings->shaderProgram, "u_shininess");
  materialSettings->u_specularIntensity = glGetUniformLocation(materialSettings->shaderProgram, "u_specularIntensity");
  materialSettings->u_specularMaterial = glGetUniformLocation(materialSettings->shaderProgram, "u_specularMaterial");
}

void ROTOM::GRAPHICS::setTexture(unsigned int *texture, unsigned char *image, int *textureWidth, int *textureHeight) {
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

  // Set the texture wrapping/filtering options (on the currently bound texture object)
  // Set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *textureWidth, *textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void ROTOM::GRAPHICS::releaseMaterial(unsigned int shaderProgram) {
  glDeleteProgram(shaderProgram);
}

void ROTOM::GRAPHICS::useMaterial(Drawable *drawable, float *projectionMatrix, float *viewMatrix, Light *light) {
  Geometry* geometry = drawable->geometry().get();
  Material* material = drawable->material().get();
  MaterialSettings* materialSettings = drawable->materialSettings().get();

  float *lightPosition = &light->lightPositionX;
  float *lightColor = &light->lightColorX;
  const float *specularIntensity = &light->specularIntensityX;
  //const float *color = material->color();
  const float *specularMaterial = material->specularMaterial_;

  glUseProgram(materialSettings->shaderProgram);

  //Texture
  glBindTexture(GL_TEXTURE_2D, material->texture());

  // Pass them to the shaders
  glUniformMatrix4fv(materialSettings->u_model, 1, GL_FALSE, glm::value_ptr(drawable->modelWorld()[0]));
  glUniformMatrix4fv(materialSettings->u_view, 1, GL_FALSE, viewMatrix);
  glUniformMatrix4fv(materialSettings->u_projection, 1, GL_FALSE, projectionMatrix);
  glUniform3f(materialSettings->u_lightPosition, lightPosition[0], lightPosition[1], lightPosition[2]);
  //glUniform4f(u_color, color[0], color[1], color[2], color[3]);
  glUniform3f(materialSettings->u_lightColor, lightColor[0], lightColor[1], lightColor[2]);
  glUniform1f(materialSettings->u_shininess, material->shininess_);
  glUniform4f(materialSettings->u_specularIntensity, specularIntensity[0], specularIntensity[1], specularIntensity[2], specularIntensity[3]);
  glUniform4f(materialSettings->u_specularMaterial, specularMaterial[0], specularMaterial[1], specularMaterial[2], specularMaterial[3]);

  glBindVertexArray(geometry->VAO());
  glDrawElements(GL_TRIANGLES, geometry->vertexCount(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void ROTOM::GRAPHICS::clearScreen() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ROTOM::GRAPHICS::loadGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int numberOfElementsPerVertex, unsigned int vertexCount, float *vertex, int *index) {
  //Release the elements in case the user load a geometry inside a geometry
  releaseGeometry(*VAO, *VBO, *EBO);

  glGenVertexArrays(1, VAO);
  glGenBuffers(1, VBO);
  glGenBuffers(1, EBO);

  glBindVertexArray(*VAO); // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  
  //Vertex
  glBindBuffer(GL_ARRAY_BUFFER, *VBO); //Bind the buffer to the GL_ARRAY_BUFFER target
  glBufferData(GL_ARRAY_BUFFER, numberOfElementsPerVertex * vertexCount, vertex, GL_STATIC_DRAW); //Copies the previously defined vertex data into the buffer's memory

  //Index
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertexCount, index, GL_STATIC_DRAW);

  //Position attribute
  int numberOfPositions = 3;
  glVertexAttribPointer(0, numberOfPositions, GL_FLOAT, GL_FALSE, numberOfElementsPerVertex, (GLvoid*)0);
  glEnableVertexAttribArray(0);

  //Normal attribute
  int numberOfNormals = 3;
  glVertexAttribPointer(1, numberOfNormals, GL_FLOAT, GL_FALSE, numberOfElementsPerVertex, (GLvoid*)(numberOfPositions * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  //UV attribute
  int numberOfUVs = 2;
  glVertexAttribPointer(2, numberOfUVs, GL_FLOAT, GL_FALSE, numberOfElementsPerVertex, (GLvoid*)((numberOfPositions + numberOfNormals) * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void ROTOM::GRAPHICS::releaseGeometry(unsigned int VAO, unsigned int VBO, unsigned int EBO) {
  if (VAO > 0) {
    glDeleteVertexArrays(1, &VAO);
  }
  if (EBO > 0) {
    glDeleteBuffers(1, &EBO);
  }
  if (VBO > 0) {
    glDeleteBuffers(1, &VBO);
  }
}