/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace ROTOM {
  class Texture {
  public:
    Texture(const char *texturePath = "../../../../img/texture.png");
    ~Texture();
  };
}

#endif //__TEXTURE_H__