/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/renderToTextureScene.h"
#include "general/input.h"
#include "general/window.h"
#include <glm/gtc/matrix_transform.hpp>

void ROTOM::RenderToTextureScene::init() {
  //Camera
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //RenderTarget
  renderTarget_.init(WindowWidth(), WindowHeight());

  //Geometry
  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  //Material
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));

  //Material renderColorToTexture
  std::shared_ptr<Material> materialRenderColorToTexture = std::shared_ptr<Material>(new Material());
  materialRenderColorToTexture->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");
  materialRenderColorToTexture->setTexture(renderTarget_.colorTexture());

  //Material renderDepthToTexture
  std::shared_ptr<Material> materialRenderDepthToTexture = std::shared_ptr<Material>(new Material());
  materialRenderDepthToTexture->setShaderFromPath("renderToDepth.vertx", "renderToDepth.frag");
  materialRenderDepthToTexture->setTexture(renderTarget_.depthTexture());

  //Drawables
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material);
  drawable1->setParent(getRoot());

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(material);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(materialRenderColorToTexture);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(materialRenderDepthToTexture);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(2.2f, 0.0f, 2.2f);
  light->materialSettings()->color_[0] = 0.8f;
  light->materialSettings()->color_[1] = 0.6f;
  light->materialSettings()->color_[2] = 0.4f;
  AddLight(light);
}

void ROTOM::RenderToTextureScene::input() {
  getCamera()->input();
}

void ROTOM::RenderToTextureScene::update() {
  if (INPUT::IsKeyDown('Z')) {
    Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
    node->setRotationX(node->rotation().x + 0.01f);
  }

  getCamera()->update();
}

void ROTOM::RenderToTextureScene::draw() {
  static bool drawRenderTarget = true;
  if (INPUT::IsKeyPressed(' ')) {
    drawRenderTarget = !drawRenderTarget;
  }

  if (drawRenderTarget) {
    renderTarget_.begin();
    {
      RenderScene(getLight().begin()->get()->projectionMatrix(), getLight().begin()->get()->viewMatrix());
      //RenderScene(getCamera()->projectionMatrix(), getCamera()->viewMatrix());
    }
    renderTarget_.end();
  }
}
