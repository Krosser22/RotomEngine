/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace ROTOM {
  struct GeneralShaderData {
    float lightPositionX = 100.0f;
    float lightPositionY = 100.0f;
    float lightPositionZ = 100.0f;

    float lightColorX = 1.0f;
    float lightColorY = 1.0f;
    float lightColorZ = 1.0f;
  };

  class Material {
  public:
    Material(const char *texturePath = "../../../../img/texture.png"); //TODO - change this path XD
    ~Material();

    //TODO - Move this to private and create functions to set/get the values
    GeneralShaderData *generalShaderData_;
    float shininess_;
    float specularIntensity_[4];
    float specularMaterial_[4];

    //Set the texture of the object
    void setTexture(const char *texturePath);
    const unsigned int texture();

    //Return the width and the height of a texture
    void textureSize(int &width, int &height);

  private:
    unsigned int texture_;
    int textureWidth_;
    int textureHeight_;
  };
}

#endif //__MATERIAL_H__