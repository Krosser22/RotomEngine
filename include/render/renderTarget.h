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
  struct FramebufferData {
    FramebufferData() {
      textureColor = 0;
      textureDepth = 0;
      framebuffer = 0;
    }
    unsigned int textureColor;
    unsigned int textureDepth;
    unsigned int framebuffer;
  };

  class RenderTarget {
  public:
    RenderTarget();
    ~RenderTarget();

    FramebufferData framebufferData_;
    
    void init(unsigned int width, unsigned int height);
    
    unsigned int *colorTexture();

    unsigned int *depthTexture();
    
    void begin();

    void end();
  };
}

#endif //__RENDER_TARGET_H__