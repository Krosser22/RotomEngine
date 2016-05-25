/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __HUD_H__
#define __HUD_H__

#include "node/camera.h"
#include "node/directionalLight.h"
#include "node/spotLight.h"
#include <memory>

namespace ROTOM {
  namespace HUD {
    void Init(std::shared_ptr<Node> root, std::vector<std::shared_ptr<DirectionalLight>> directionalLights, std::vector<std::shared_ptr<SpotLight>> spotLights, Camera *camera);

    void Draw();

    void DrawMenu();

    void DrawSceneTree();

    void DrawDetails();

    void DrawContent();

    void DrawSceneRender();

    void DrawNodes(Node *node, float offsetX);

    void DrawNode(Node *node);

    void DrawDrawable(Drawable *drawable);

    void DrawCamera(Camera *camera);

    void DrawLight(DirectionalLight *light);

    void DrawGeometry(Geometry *geometry);

    void DrawMaterial(Material *material);

    void DrawMaterialSettings(MaterialSettings *materialSettings);
  }
}

#endif //__HUD_H__