/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "geometry.h"
#include "material.h"
#include "materialSettings.h"
#include "node.h"
#include <memory>

namespace ROTOM {
  struct DrawableData {
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> material;
    std::shared_ptr<MaterialSettings> materialSettings;
  };

  static DrawableData drawableData[ROTOM::kNodeDataAmount];
  static unsigned int nextDrawableID = 0;

  class Drawable : public Node {
  public:
    Drawable();
    Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, unsigned int parent);
    virtual ~Drawable();

    unsigned int drawableID();
    
    void setGeometry(std::shared_ptr<Geometry> geometry);
    std::shared_ptr<Geometry> geometry();

    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> material();

    void setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings);
    std::shared_ptr<MaterialSettings> materialSettings();

  private:
    unsigned int drawableID_;
  };
}

#endif //__DRAWABLE_H__