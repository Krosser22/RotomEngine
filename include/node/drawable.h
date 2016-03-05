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
  class Drawable : public Node {
  public:
    Drawable(char *name);
    virtual ~Drawable();
    
    void setGeometry(std::shared_ptr<Geometry> geometry);
    std::shared_ptr<Geometry> geometry();

    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> material();

    void setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings);
    std::shared_ptr<MaterialSettings> materialSettings();

  private:
    std::shared_ptr<ROTOM::Geometry> geometry_;
    std::shared_ptr<ROTOM::Material> material_;
    std::shared_ptr<ROTOM::MaterialSettings> materialSettings_;
  };
}

#endif //__DRAWABLE_H__