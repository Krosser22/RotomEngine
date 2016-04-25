/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __RENDER_TARGET_H__
#define __RENDER_TARGET_H__

namespace ROTOM {
  class RenderTarget {
  public:
    RenderTarget();
    ~RenderTarget();
    
    void init(unsigned int width, unsigned int height);
    
    unsigned int *colorTexture();

    unsigned int *depthTexture();
    
    void begin();

    void end();
  };
}

#endif //__RENDER_TARGET_H__