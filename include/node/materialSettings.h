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

    //Set the color of the object (0.0f - 1.0f)
    void setColor(const float r, const float g, const float b, const float a = 1.0f);
    const float *color();

    float color_[4];
  };
}

#endif //__MATERIAL_SETTINGS_H__