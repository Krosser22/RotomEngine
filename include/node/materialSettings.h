/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_SETTINGS_H__
#define __MATERIAL_SETTINGS_H__

namespace ROTOM {
  class MaterialSettings {
  public:
    MaterialSettings();
    ~MaterialSettings();

    void setColor(float r, float g, float b, float a = 1.0f);

    float color_[4];
  };
}

#endif //__MATERIAL_SETTINGS_H__