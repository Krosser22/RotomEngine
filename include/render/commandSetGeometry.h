/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_SET_GEOMETRY_H__
#define __COMMAND_SET_GEOMETRY_H__

#include "command.h"
#include "node/drawable.h"
#include "node/directionalLight.h"

namespace ROTOM {
  class CommandSetGeometry : public Command {
  public:
    CommandSetGeometry();
    virtual ~CommandSetGeometry();

    void run();
    
    void setInput(std::shared_ptr<Geometry::GeometryData> geometryData, Geometry *geometry);

  private:
    std::shared_ptr<Geometry::GeometryData> geometryData_;
    Geometry *geometry_;
  };
}

#endif //__COMMAND_SET_GEOMETRY_H__