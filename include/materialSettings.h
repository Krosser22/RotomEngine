/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_SETTINGS_H__
#define __MATERIAL_SETTINGS_H__

namespace ROTOM {
  class MaterialSettings {
  public:
    MaterialSettings();
    ~MaterialSettings();

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

    //Set the color of the object (0.0f - 1.0f)
    void setColor(const float r, const float g, const float b, const float a = 1.0f);
    const float *color();

    float color_[4];
  };
}

#endif //__MATERIAL_SETTINGS_H__