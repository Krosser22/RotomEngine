/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "drawable.h"
#include "camera.h"

namespace ROTOM {
  class Chunk {
  public:
    Chunk() {};
    Chunk(char *name) {};
    virtual ~Chunk() {};

    //Set the amount of rows and cols of the chunk and the max of height it is allowed to have
    void init(std::shared_ptr<Node> parent, Camera *camera, unsigned int maxHeight = 256);

    void update();

    void setMaxHeight(unsigned int maxHeight);

  private:
    void updateGeometry();

    float getHeight(float x, float y, float z);
  };
}

#endif //__CHUNK_H__