/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#include <memory>

class Obj_loader {
public:
  Obj_loader() {};
  ~Obj_loader() {};

  bool init(const char *file, int size_x = 1, int size_y = 1, int size_z = 1);

  bool debug = false;

private:
  int dataCount_;
  std::shared_ptr<float> bufferData_;

  int indexCount_;
  std::shared_ptr<int> bufferIndex_;
};

#endif //__OBJ_LOADER_H__