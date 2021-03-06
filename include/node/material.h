/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace ROTOM {
  struct ShaderData {
    ShaderData() {
      shaderProgram = 0;
      u_color = 0;
      u_model = 0;
      u_view = 0;
      u_projection = 0;
      u_lightPosition = 0;
      u_lightColor = 0;
      u_texture = 0;
      u_shininess = 0;
      u_specularIntensity = 0;
      u_specularMaterial = 0;
      u_ambientStrength = 0;
      u_viewPosition = 0;
      u_lightSpaceMatrix = 0;
      u_colorMap = 0;
      u_depthMap = 0;
      u_shadows = 0;
      u_nearPlane = 0;
      u_farPlane = 0;
    }
    unsigned int shaderProgram;
    unsigned int u_color;
    unsigned int u_model;
    unsigned int u_view;
    unsigned int u_projection;
    unsigned int u_lightPosition;
    unsigned int u_lightColor;
    unsigned int u_texture;
    unsigned int u_shininess;
    unsigned int u_specularIntensity;
    unsigned int u_specularMaterial;
    unsigned int u_ambientStrength;
    unsigned int u_viewPosition;
    unsigned int u_lightSpaceMatrix;
    unsigned int u_colorMap;
    unsigned int u_depthMap;
    unsigned int u_shadows;
    unsigned int u_nearPlane;
    unsigned int u_farPlane;
  };

  struct MaterialData {
    float shininess;
    float specularMaterial[3];
    float ambientStrength;
  };

  class Material {
  public:
    Material(const char *texturePath = "../../../../img/texture.png");
    ~Material();

    ShaderData shaderData_;
    MaterialData materialData_;

    unsigned int texture_;

    void setShader(const char *vertexShaderSource, const char *fragmentShaderSource);
    void setShaderFromPath(const char *vertexShaderPath, const char *fragmentShaderPath);

    //Set the texture of the object
    void setTexture(unsigned char *texture);
    void setTexture(unsigned int *texture);
    void setTextureFromPath(const char *path);
    const unsigned int texture();

    //Return the width and the height of a texture
    void textureSize(int &width, int &height);

  private:
    int textureWidth_;
    int textureHeight_;
  };
}

#endif //__MATERIAL_H__