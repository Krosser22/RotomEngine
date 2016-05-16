/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/shadowScene.h"
#include "general/input.h"
#include "general/window.h"
#include "general/time.h"
#include <glm/gtc/matrix_transform.hpp>

void ROTOM::ShadowScene::init() {
  //Camera
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(7.0f, 1.22f, -1.0f);
  getCamera()->setPitch(-10.0f);
  getCamera()->setYaw(190.0f);

  //RenderTarget
  renderTarget_.init(WindowWidth(), WindowHeight());

  //Geometry
  geometry_ = std::shared_ptr<Geometry>(new Geometry());
  geometryFloor_ = std::shared_ptr<Geometry>(new Geometry());
  //geometryFloor_->loadGeometry("Nanosuit/nanosuit");
  geometryNanosuit_ = std::shared_ptr<Geometry>(new Geometry());
  geometryNanosuit_->loadGeometry("Nanosuit/nanosuit");

  //ShadowMaterial
  std::shared_ptr<Material> shadowMaterial = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));
  shadowMaterial->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");

  //Material renderDepthToTexture
  std::shared_ptr<Material> materialRenderDepthToTexture = std::shared_ptr<Material>(new Material());
  materialRenderDepthToTexture->setShaderFromPath("renderToDepth.vertx", "renderToDepth.frag");
  materialRenderDepthToTexture->setTexture(renderTarget_.depthTexture());
  
  //Drawables
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));
  std::shared_ptr<Drawable> drawable5 = std::shared_ptr<Drawable>(new Drawable("nanosuit"));
  std::shared_ptr<Drawable> drawable6 = std::shared_ptr<Drawable>(new Drawable("depth"));
  std::shared_ptr<Drawable> drawable7 = std::shared_ptr<Drawable>(new Drawable("floor"));

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(shadowMaterial);
  drawable1->setParent(getRoot());

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(shadowMaterial);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(shadowMaterial);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(shadowMaterial);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  drawable5->setGeometry(geometryNanosuit_);
  drawable5->setMaterial(shadowMaterial);
  drawable5->setParent(getRoot());
  drawable5->setPosition(0.6f, 0.6f, -1.0f);

  drawable6->setGeometry(geometry_);
  drawable6->setMaterial(materialRenderDepthToTexture);
  drawable6->setParent(getRoot());
  drawable6->setPosition(1.5f, 1.0f, 0.0f);

  drawable7->setGeometry(geometryFloor_);
  drawable7->setMaterial(shadowMaterial);
  drawable7->setParent(getRoot());
  drawable7->setPosition(0.0f, 0.0f, -6.0f);
  drawable7->setScale(100.0f, 100.0f, 1.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.5f, 1.0f, 3.0f);
  //light->materialSettings()->setColor(0.2f, 0.4f, 0.6f);
  AddLight(light);
}

void ROTOM::ShadowScene::input() {
  getCamera()->input();
}

void ROTOM::ShadowScene::update() {
  if (INPUT::IsKeyDown('Z')) {
    Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
    node->setRotationX(node->rotation().x + 0.01f);
  }

  getCamera()->update();

  static bool cameraAutoRotate = false;

  if (INPUT::IsKeyPressed(' ')) {
    cameraAutoRotate = !cameraAutoRotate;
  }

  if (cameraAutoRotate) {
    getLight().begin()->get()->setPosition(
      sin(ROTOM::TIME::appTime()) * 5.0f,
      3.0f /*+ cos(ROTOM::TIME::appTime()) * 1.0f*/,
      cos(ROTOM::TIME::appTime()) * 5.0f);
  }
}

void ROTOM::ShadowScene::draw() {
  renderTarget_.begin();
  {
    RenderScene(getLight().begin()->get()->projectionMatrix(), getLight().begin()->get()->viewMatrix(), getLight().begin()->get()->pos());
    //RenderScene(getCamera()->projectionMatrix(), getCamera()->viewMatrix(), getCamera()->position());
  }
  renderTarget_.end();
}