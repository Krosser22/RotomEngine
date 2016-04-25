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
    void init(unsigned int rows = 10, unsigned int cols = 10, unsigned int maxHeight = 256);

    void setRows(unsigned int rows);

    void setCols(unsigned int cols);

    void setMaxHeight(unsigned int maxHeight);

    //Node
    void move(const float x, const float y, const float z);
    void setParent(std::shared_ptr<Node> parent);
  };
}

#endif //__CHUNK_H__