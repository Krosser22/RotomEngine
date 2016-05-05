/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/materialSettings.h"

ROTOM::MaterialSettings::MaterialSettings() {
  color_[0] = 1.0f;
  color_[1] = 1.0f;
  color_[2] = 1.0f;
  color_[3] = 1.0f;
}

ROTOM::MaterialSettings::~MaterialSettings() {}


void ROTOM::MaterialSettings::setColor(float r, float g, float b, float a) {
  color_[0] = r;
  color_[1] = g;
  color_[2] = b;
  color_[3] = a;
}