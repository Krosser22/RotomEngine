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
    Drawable();
    Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, std::shared_ptr<Node> parent);
    virtual ~Drawable();
    
    void setGeometry(std::shared_ptr<Geometry> geometry);
    std::shared_ptr<Geometry> geometry();

    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> material();

    std::shared_ptr<MaterialSettings> materialSettings();

  private:
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<MaterialSettings> materialSettings_;
  };
}

#endif //__DRAWABLE_H__