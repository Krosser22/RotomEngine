/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/renderTarget.h"
#include "render/graphics.h"

ROTOM::RenderTarget::RenderTarget() {}

ROTOM::RenderTarget::~RenderTarget() {}

void ROTOM::RenderTarget::init(unsigned int width, unsigned int height) {
  GRAPHICS::genRenderBuffer(
    &framebufferData_.textureColor, 
    &framebufferData_.textureDepth, 
    &framebufferData_.framebuffer, 
    width, 
    height);
}

unsigned int *ROTOM::RenderTarget::colorTexture() {
  return &framebufferData_.textureColor;
}

unsigned int *ROTOM::RenderTarget::depthTexture() {
  return &framebufferData_.textureDepth;
}

void ROTOM::RenderTarget::begin() {
  GRAPHICS::beginFramebuffer(this);
}

void ROTOM::RenderTarget::end() {
  GRAPHICS::endFramebuffer();
}