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
  class Drawable : public Node{
  public:
    Drawable();
    Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, std::shared_ptr<MaterialSettings> materialSettings, Node *parent);
    virtual ~Drawable();
    
    void setGeometry(std::shared_ptr<Geometry> geometry);
    std::shared_ptr<Geometry> geometry();

    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> material();

    void setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings);
    std::shared_ptr<MaterialSettings> materialSettings();

    void setShader(const char *vertexShaderSource, const char *fragmentShaderSource);

    //Set the color of the object (0.0f - 1.0f)
    void setColor(const float r, const float g, const float b, const float a = 1.0f);
    const float *color();

  private:
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<MaterialSettings> materialSettings_;

    float color_[4];
  };
}

#endif //__DRAWABLE_H__