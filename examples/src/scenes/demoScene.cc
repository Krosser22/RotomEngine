/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/demoScene.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"

void ROTOM::DemoScene::init() {
  //Camera
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(-4.0f, 1.0f, 6.0f);
  //getCamera()->setPitch(-45.0f);
  getCamera()->setYaw(-66.0f);

  //RenderTarget
  renderTarget_.init(WindowWidth(), WindowHeight());
  postProcess_.init(WindowWidth(), WindowHeight());

  //Geometry
  geometry_ = std::shared_ptr<Geometry>(new Geometry());
  geometryMutable_ = std::shared_ptr<Geometry>(new Geometry());
  geometryHUD_ = std::shared_ptr<Geometry>(new Geometry());

  //Wall
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("shadows/2_lights.vertx", "shadows/2_lights.frag");
  material->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");
  drawable_wall_ = std::shared_ptr<Drawable>(new Drawable("Wall"));
  drawable_wall_->setGeometry(geometry_);
  drawable_wall_->setMaterial(material);
  drawable_wall_->setParent(getRoot());
  drawable_wall_->setPosition(0.0f, 0.0f, -5.0f);
  drawable_wall_->setScale(100.0f, 100.0f, 1.0f);

  //Material1: Color
  std::shared_ptr<Material> material_color = std::shared_ptr<Material>(new Material());
  material_color->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");
  drawable_color_ = std::shared_ptr<Drawable>(new Drawable("Color"));
  drawable_color_->setGeometry(geometryMutable_);
  drawable_color_->setMaterial(material_color);
  drawable_color_->setParent(getRoot());
  drawable_color_->setPosition(0.0f, 0.0f, 0.0f);

  //Material2: Color + Texture
  std::shared_ptr<Material> material_texture = std::shared_ptr<Material>(new Material());
  material_texture->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");
  drawable_texture_ = std::shared_ptr<Drawable>(new Drawable("Texture"));
  drawable_texture_->setGeometry(geometryMutable_);
  drawable_texture_->setMaterial(material_texture);
  drawable_texture_->setParent(drawable_color_);
  drawable_texture_->setPosition(0.0f, 5.0f, 0.0f);

  //Material3: Color + Texture + DiffuseLight
  std::shared_ptr<Material> material_diffuseLight = std::shared_ptr<Material>(new Material());
  material_diffuseLight->setShaderFromPath("basics/3_DiffuseLight.vertx", "basics/3_DiffuseLight.frag");
  drawable_diffuseLight_ = std::shared_ptr<Drawable>(new Drawable("Diffuse"));
  drawable_diffuseLight_->setGeometry(geometryMutable_);
  drawable_diffuseLight_->setMaterial(material_diffuseLight);
  drawable_diffuseLight_->setParent(drawable_color_);
  drawable_diffuseLight_->setPosition(0.0f, 10.0f, 0.0f);

  //Material4: Color + Texture + DiffuseLight + SpecularLight
  std::shared_ptr<Material> material_specularLight = std::shared_ptr<Material>(new Material());
  material_specularLight->setShaderFromPath("basics/4_SpecularLight.vertx", "basics/4_SpecularLight.frag");
  drawable_specularLight_ = std::shared_ptr<Drawable>(new Drawable("Specular"));
  drawable_specularLight_->setGeometry(geometryMutable_);
  drawable_specularLight_->setMaterial(material_specularLight);
  drawable_specularLight_->setParent(drawable_color_);
  drawable_specularLight_->setPosition(0.0f, 15.0f, 0.0f);

  //Material5: Color + Texture + DiffuseLight + SpecularLight + Blinn-Phong
  std::shared_ptr<Material> material_Blinn_Phong = std::shared_ptr<Material>(new Material());
  material_Blinn_Phong->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");
  drawable_Blinn_Phong_ = std::shared_ptr<Drawable>(new Drawable("BlinnPhong"));
  drawable_Blinn_Phong_->setGeometry(geometryMutable_);
  drawable_Blinn_Phong_->setMaterial(material_Blinn_Phong);
  drawable_Blinn_Phong_->setParent(drawable_color_);
  drawable_Blinn_Phong_->setPosition(0.0f, 20.0f, 0.0f);

  //Material6: Color + Texture + DiffuseLight + Blinn-Phong + Shadow
  std::shared_ptr<Material> material_shadow = std::shared_ptr<Material>(new Material());
  material_shadow->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");
  drawable_shadow_ = std::shared_ptr<Drawable>(new Drawable("Shadow"));
  drawable_shadow_->setGeometry(geometryMutable_);
  drawable_shadow_->setMaterial(material_shadow);
  drawable_shadow_->setParent(drawable_color_);
  drawable_shadow_->setPosition(0.0f, 25.0f, 0.0f);

  //Material7: Color + Texture + DiffuseLight + Blinn-Phong + Shadow + MultipleLight
  /*std::shared_ptr<Material> material_multipleLight = std::shared_ptr<Material>(new Material());
  material_multipleLight->setShaderFromPath("shadows/2_lights.vertx", "shadows/2_lights.frag");
  drawable_multipleLights_ = std::shared_ptr<Drawable>(new Drawable("MultipleLight"));
  drawable_multipleLights_->setGeometry(geometryMutable_);
  drawable_multipleLights_->setMaterial(material_color);
  drawable_multipleLights_->setParent(drawable_color_);
  drawable_multipleLights_->setPosition(0.0f, 30.0f, 0.0f);*/

  //Material8: Depth
  std::shared_ptr<Material> material_depth = std::shared_ptr<Material>(new Material());
  material_depth->setShaderFromPath("depthBuffer.vertx", "depthBuffer.frag");
  drawable_depth_ = std::shared_ptr<Drawable>(new Drawable("Depth"));
  drawable_depth_->setGeometry(geometry_);
  drawable_depth_->setMaterial(material_depth);
  drawable_depth_->setParent(drawable_color_);
  drawable_depth_->setPosition(0.0f, 30.0f, 0.0f);
  drawable_depth_->setScale(1.0f, 1.0f, 100.0f);

  //Transparent Texture
  std::shared_ptr<Material> material_transparent = std::shared_ptr<Material>(new Material("../../../../img/window.png"));
  material_transparent->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");
  std::shared_ptr<Drawable> drawable_Transparent = std::shared_ptr<Drawable>(new Drawable("Transparent"));
  drawable_Transparent->setGeometry(geometry_);
  drawable_Transparent->setMaterial(material_transparent);
  drawable_Transparent->setParent(drawable_color_);
  drawable_Transparent->setPosition(0.0f, 35.0f, 0.0f);

  //Material9: Reflect
  /*std::shared_ptr<Material> material_reflect = std::shared_ptr<Material>(new Material());
  material_reflect->setShaderFromPath("reflect.vertx", "reflect.frag");
  drawable_reflect_ = std::shared_ptr<Drawable>(new Drawable("Reflect"));
  drawable_reflect_->setGeometry(geometryMutable_);
  drawable_reflect_->setMaterial(material_reflect);
  drawable_reflect_->setParent(drawable_color_);
  drawable_reflect_->setPosition(0.0f, 35.0f, 0.0f);*/

  //Material10: Refract
  /*std::shared_ptr<Material> material_refract = std::shared_ptr<Material>(new Material());
  material_refract->setShaderFromPath("refract.vertx", "refract.frag");
  drawable_refract_ = std::shared_ptr<Drawable>(new Drawable("Refract"));
  drawable_refract_->setGeometry(geometryMutable_);
  drawable_refract_->setMaterial(material_refract);
  drawable_refract_->setParent(drawable_color_);
  drawable_refract_->setPosition(0.0f, 40.0f, 0.0f);*/

  //Material11: RenderDepthToTexture
  /*std::shared_ptr<Material> material_renderDepthToTexture = std::shared_ptr<Material>(new Material());
  material_renderDepthToTexture->setShaderFromPath("renderToDepth.vertx", "renderToDepth.frag");
  material_renderDepthToTexture->setTexture(renderTarget_.depthTexture());
  drawable_screenTexture_ = std::shared_ptr<Drawable>(new Drawable("ScreenTexture"));
  drawable_screenTexture_->setGeometry(geometry_);
  drawable_screenTexture_->setMaterial(material_renderDepthToTexture);
  drawable_screenTexture_->setParent(drawable_color_);
  drawable_screenTexture_->setPosition(0.0f, 50.0f, 0.0f);*/

  //Material12: RenderColorToTexture
  material_renderColorToTexture_ = std::shared_ptr<Material>(new Material());
  material_renderColorToTexture_->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");
  //material_renderColorToTexture->setShaderFromPath("screenTexture.vertx", "screenTexture.frag");
  drawable_renderToDepth_ = std::shared_ptr<Drawable>(new Drawable("ScreenTexture"));
  drawable_renderToDepth_->setGeometry(geometryHUD_);
  drawable_renderToDepth_->setMaterial(material_renderColorToTexture_);
  drawable_renderToDepth_->setParent(drawable_color_);
  drawable_renderToDepth_->setPosition(0.0f, 40.0f, 0.0f);

  //Cubemap
  //cubemap_.init("");

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
  spotLight1->materialSettings()->setColor(0.0f, 1.0f, 1.0f);
  addSpotLight(spotLight1);

  std::shared_ptr<SpotLight> spotLight2 = std::shared_ptr<SpotLight>(new SpotLight("SpotLight2"));
  spotLight2->setParent(getRoot());
  spotLight2->setPosition(0.0f, 3.0f, 0.0f);
  spotLight2->materialSettings()->setColor(1.0f, 1.0f, 0.0f);
  addSpotLight(spotLight2);

  //Sound
  sound_ = new ROTOM::SOUND::Sound("../../../../sound/elevator.ogg");
  sound_->setLoop(true);
  sound_->play();
}

static bool post = false;
void ROTOM::DemoScene::input() {
  //Add Cube
  /*if (INPUT::IsKeyPressed('R')) {
    static float posX = -2.0f;
    std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
    std::shared_ptr<Drawable> drawableNew = std::shared_ptr<Drawable>(new Drawable("input"));
    drawableNew->setGeometry(geometry_);
    drawableNew->setMaterial(material);
    drawableNew->setParent(getRoot()->getChildAt(0));
    drawableNew->setPositionX(posX);
    posX -= 1.0f;
  }*/

  static bool isShader = false;
  if (INPUT::IsKeyPressed('1')) {
    if (isShader) {
      material_renderColorToTexture_->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");
    } else {
      material_renderColorToTexture_->setShaderFromPath("screenTexture.vertx", "screenTexture.frag");
    }
    isShader = !isShader;
  }
  if (INPUT::IsKeyPressed('2')) {
    post = !post;
  }

  getCamera()->input();
}

void ROTOM::DemoScene::update() {
  //Movement
  static bool rightMovement = false;
  if (INPUT::IsKeyPressed(' ')) {
    rightMovement = !rightMovement;
  }
  if (rightMovement) {
    drawable_color_->moveY(-0.022f);
  }

  //Camera movement
  getCamera()->update();

  //Color
  drawable_color_->materialSettings()->setColor(sin(TIME::appTime() * 2), sin(TIME::appTime() * 4), sin(TIME::appTime() * 6));
}

void ROTOM::DemoScene::draw() {
  //cubemap_.draw(getCamera()->projectionMatrix(), getCamera()->viewMatrix());
  renderTarget_.begin();
  {
    RenderScene(getDirectionalLights().begin()->get()->projectionMatrix(), getDirectionalLights().begin()->get()->viewMatrix(), getDirectionalLights().begin()->get()->pos());
    //RenderScene(getCamera()->projectionMatrix(), getCamera()->viewMatrix(), getCamera()->position());
  }
  renderTarget_.end();

  if (post) {
    postProcess_.begin();
  }
}

void ROTOM::DemoScene::postDraw() {
  if (post) {
    postProcess_.end(true);
  }
}