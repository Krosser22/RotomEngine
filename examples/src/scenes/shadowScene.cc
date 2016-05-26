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
  getCamera()->setPosition(12.0f, 1.22f, -1.0f);
  getCamera()->setPitch(-10.0f);
  getCamera()->setYaw(190.0f);

  //RenderTarget
  renderTarget_.init(WindowWidth(), WindowHeight());

  //Geometry
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Geometry> geometryFloor = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Geometry> geometryNanosuit = std::shared_ptr<Geometry>(new Geometry());
  geometryNanosuit->loadGeometry("Nanosuit/nanosuit");

  //ShadowMaterial
  std::shared_ptr<Material> shadowMaterial = std::shared_ptr<Material>(new Material("../../../../img/no_texture.png"));
  //shadowMaterial->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");
  shadowMaterial->setShaderFromPath("shadows/2_lights.vertx", "shadows/2_lights.frag");

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

  drawable1->setGeometry(geometry);
  drawable1->setMaterial(shadowMaterial);
  drawable1->setParent(getRoot());

  drawable2->setGeometry(geometry);
  drawable2->setMaterial(shadowMaterial);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry);
  drawable3->setMaterial(shadowMaterial);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry);
  drawable4->setMaterial(shadowMaterial);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  drawable5->setGeometry(geometryNanosuit);
  drawable5->setMaterial(shadowMaterial);
  drawable5->setParent(getRoot());
  drawable5->setPosition(0.6f, 0.6f, -1.0f);

  drawable6->setGeometry(geometry);
  drawable6->setMaterial(materialRenderDepthToTexture);
  drawable6->setParent(getRoot());
  drawable6->setPosition(1.5f, 1.0f, 0.0f);

  drawable7->setGeometry(geometryFloor);
  drawable7->setMaterial(shadowMaterial);
  drawable7->setParent(getRoot());
  drawable7->setPosition(0.0f, 0.0f, -6.0f);
  drawable7->setScale(100.0f, 100.0f, 1.0f);

  //Light
  clearLights();

  //Directional Light
  std::shared_ptr<DirectionalLight> directionalLight = std::shared_ptr<DirectionalLight>(new DirectionalLight("DirectionalLight"));
  directionalLight->setParent(getRoot());
  directionalLight->setPosition(1.5f, 1.0f, 3.0f);
  addDirectionalLight(directionalLight);

  //Spot Light
  std::shared_ptr<SpotLight> spotLight1 = std::shared_ptr<SpotLight>(new SpotLight("SpotLight1"));
  spotLight1->setParent(getRoot());
  spotLight1->setPosition(2.2f, 3.0f, 2.2f);
  spotLight1->materialSettings()->setColor(0.2f, 0.4f, 0.6f);
  addSpotLight(spotLight1);

  std::shared_ptr<SpotLight> spotLight2 = std::shared_ptr<SpotLight>(new SpotLight("SpotLight2"));
  spotLight2->setParent(getRoot());
  spotLight2->setPosition(2.2f, 3.0f, -2.2f);
  spotLight2->materialSettings()->setColor(0.8f, 0.2f, 0.5f);
  addSpotLight(spotLight2);
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

  static bool cameraAutoRotate = true;

  if (INPUT::IsKeyPressed(' ')) {
    cameraAutoRotate = !cameraAutoRotate;
  }

  if (cameraAutoRotate) {
    getSpotLights().begin()->get()->setPositionX(sin(ROTOM::TIME::appTime()) * 0.8f);
    getSpotLights().begin()->get()->setPositionY(3.0f /*+ cos(ROTOM::TIME::appTime()) * 1.0f*/);
    getSpotLights().begin()->get()->setPositionZ(cos(ROTOM::TIME::appTime()) * 0.8f);
  }
}

void ROTOM::ShadowScene::draw() {
  renderTarget_.begin();
  {
    RenderScene(getDirectionalLights().begin()->get()->projectionMatrix(), getDirectionalLights().begin()->get()->viewMatrix(), getDirectionalLights().begin()->get()->pos());
    //RenderScene(getCamera()->projectionMatrix(), getCamera()->viewMatrix(), getCamera()->position());
  }
  renderTarget_.end();
}

void ROTOM::ShadowScene::postDraw() {
  
}