/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __HUD_H__
#define __HUD_H__

#include "node/drawable.h"
#include "node/camera.h"
#include "node/light.h"
#include <memory>

namespace ROTOM {
  namespace HUD {
    void Draw(std::shared_ptr<Node> root, std::vector<std::shared_ptr<Light>> lights, Camera *camera);

    void DrawNode(Node *node);

    void DrawDrawable(Drawable *drawable);

    void DrawCamera(Camera *camera);

    void DrawLight(Light *light);

    void DrawGeometry(Geometry *geometry);

    void DrawMaterial(Material *material);
  }
}

#endif //__HUD_H__