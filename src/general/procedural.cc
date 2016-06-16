/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/procedural.h"
#include <stb_perlin.h>

float ROTOM::PROCEDURAL::perlinNoise(float x, float y, float z, int x_wrap, int y_wrap, int z_wrap) {
  return stb_perlin_noise3(x, y, z, x_wrap, y_wrap, z_wrap);
}