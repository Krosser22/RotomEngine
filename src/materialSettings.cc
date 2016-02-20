/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "materialSettings.h"

ROTOM::MaterialSettings::MaterialSettings() {
  setColor(1.0f, 1.0f, 1.0f, 1.0f);
}

ROTOM::MaterialSettings::~MaterialSettings() {}

void ROTOM::MaterialSettings::setColor(const float r, const float g, const float b, const float a) {
  color_[0] = r;
  color_[1] = g;
  color_[2] = b;
  color_[3] = a;
}

const float *ROTOM::MaterialSettings::color() {
  return color_;
}