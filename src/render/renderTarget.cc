/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/renderTarget.h"
#include "render/graphics.h"

ROTOM::Drawable drawable;
ROTOM::CommandDrawObjectData commandDrawObjectData;

ROTOM::RenderTarget::RenderTarget() {}

ROTOM::RenderTarget::~RenderTarget() {}

void ROTOM::RenderTarget::init(unsigned int width, unsigned int height) {
  GRAPHICS::genRenderBuffer(
    &framebufferData_.textureColor, 
    &framebufferData_.textureDepth, 
    &framebufferData_.framebuffer, 
    width, 
    height);

  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../img/no_texture.png"));
  material->setShaderFromPath("light.vertx", "light.frag");
  
  drawable.setGeometry(geometry);
  drawable.setMaterial(material);

  commandDrawObjectData.visible = true;
  commandDrawObjectData.shadows = false;
  commandDrawObjectData.materialSettings = *drawable.materialSettings().get();
  commandDrawObjectData.shaderData = material->shaderData_;
  commandDrawObjectData.geometry_VAO = *geometry->VAO();
  commandDrawObjectData.geometry_veterCount = geometry->vertexCount();
  commandDrawObjectData.material_texture = material->texture();
  commandDrawObjectData.materialData = material->materialData_;
  float *worldMatrix = glm::value_ptr(*drawable.worldMatrix());
  for (int i = 0; i < 16; ++i) {
    commandDrawObjectData.drawable_worldMatrix[i] = worldMatrix[i];
  }
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

void ROTOM::RenderTarget::end(bool drawOnScreen) {
  GRAPHICS::endFramebuffer();

  if (drawOnScreen) {
    GRAPHICS::drawObject(&commandDrawObjectData);
  }
}