/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

namespace ROTOM {
  enum NodeType {
    kNodeType_Node,
    kNodeType_Drawable,
    kNodeType_Light,
  };

  enum Content {
    kContent_None,
    kContent_Geometry,
    kContent_Shaders,
    kContent_Texture,
  };

  static const char *kPath_objFiles = "../../../../obj/";
  static const char *kPath_imgFiles = "../../../../img/";
  static const char *kPath_shaderFiles = "../../../../shaders/";
}
#endif //__CONSTANTS_H__