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

namespace ROTOM {
  class Chunk {
  public:
    Chunk();
    Chunk(char *name);
    virtual ~Chunk();

    //Set the amount of rows and cols of the chunk and the max of height it is allowed to have
    void init(std::shared_ptr<Node> parent, unsigned int rows = 1, unsigned int cols = 1, unsigned int maxHeight = 256);

    void update();

    void setRows(unsigned int rows);

    void setCols(unsigned int cols);

    void setMaxHeight(unsigned int maxHeight);

    //Node
    void move(const float x, const float y, const float z);
    void setParent(std::shared_ptr<Node> parent);

  private:
    float amountOfChange_ = 0.01f;
  };
}

#endif //__CHUNK_H__