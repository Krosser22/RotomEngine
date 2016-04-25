/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/renderTarget.h"
#include "render/graphics.h"

unsigned int textureColor;
unsigned int textureDepth;
unsigned int framebuffer;

ROTOM::RenderTarget::RenderTarget() {}

ROTOM::RenderTarget::~RenderTarget() {}

void ROTOM::RenderTarget::init(unsigned int width, unsigned int height) {
  GRAPHICS::genRenderBuffer(&textureColor, &textureDepth, &framebuffer, width, height);
}

unsigned int *ROTOM::RenderTarget::colorTexture() {
  return &textureColor;
}

unsigned int *ROTOM::RenderTarget::depthTexture() {
  return &textureDepth;
}

void ROTOM::RenderTarget::begin() {
  GRAPHICS::beginFramebuffer(framebuffer);
}

void ROTOM::RenderTarget::end() {
  GRAPHICS::endFramebuffer();
}