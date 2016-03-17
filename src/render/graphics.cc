/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/graphics.h"

float ROTOM::GRAPHICS::getTime() {
  return (float)glfwGetTime();
}

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
  shaderData->u_ambientStrength = glGetUniformLocation(shaderData->shaderProgram, "u_ambientStrength");
}

void ROTOM::GRAPHICS::setTexture(unsigned int *texture, unsigned char *image, int *textureWidth, int *textureHeight) {
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

  // Set the texture wrapping/filtering options (on the currently bound texture object)
  // Set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // Set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *textureWidth, *textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void ROTOM::GRAPHICS::releaseMaterial(unsigned int shaderProgram) {
  glDeleteProgram(shaderProgram);
}

void ROTOM::GRAPHICS::drawMaterial(CommandDrawObjectData *commandDrawObjectData, std::vector<std::shared_ptr<Light>> *lights, float *projectionMatrix, float *viewMatrix) {
  ShaderData *shaderData = &commandDrawObjectData->shaderData;
  MaterialSettings* materialSettings = &commandDrawObjectData->materialSettings;
  const float *specularMaterial = commandDrawObjectData->materialData.specularMaterial;
  const float *color = materialSettings->color_;

  glUseProgram(shaderData->shaderProgram);

  //Texture
  glBindTexture(GL_TEXTURE_2D, commandDrawObjectData->material_texture);

  //Node
  glUniformMatrix4fv(shaderData->u_model, 1, GL_FALSE, commandDrawObjectData->drawable_modelWorld);
  glUniformMatrix4fv(shaderData->u_view, 1, GL_FALSE, viewMatrix);
  glUniformMatrix4fv(shaderData->u_projection, 1, GL_FALSE, projectionMatrix);

  //Material
  glUniform1f(shaderData->u_shininess, commandDrawObjectData->materialData.shininess);
  glUniform3f(shaderData->u_specularMaterial, specularMaterial[0], specularMaterial[1], specularMaterial[2]);
  glUniform1f(shaderData->u_ambientStrength, commandDrawObjectData->materialData.ambientStrength);
  
  //Material Settings
  glUniform4f(shaderData->u_color, color[0], color[1], color[2], color[3]);

  //Light
  for (unsigned int i = 0; i < lights->size(); ++i) {
    const float *lightPosition = &lights->at(i)->position()[0];
    const float *lightColor = lights->at(i)->materialSettings()->color_;
    const float *specularIntensity = lights->at(i)->specularIntensity;
    glUniform3f(shaderData->u_lightPosition, lightPosition[0], lightPosition[1], lightPosition[2]);
    glUniform3f(shaderData->u_lightColor, lightColor[0], lightColor[1], lightColor[2]);
    glUniform3f(shaderData->u_specularIntensity, specularIntensity[0], specularIntensity[1], specularIntensity[2]);
  }

  glBindVertexArray(commandDrawObjectData->geometry_VAO);
  glDrawElements(GL_TRIANGLES, commandDrawObjectData->geometry_veterCount, GL_UNSIGNED_INT, 0);
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