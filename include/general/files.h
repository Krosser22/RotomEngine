/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __FILES_H__
#define __FILES_H__

#include <memory>
#include <string>

namespace ROTOM {
  namespace FILES {
    void ReadFile(const char *path, std::shared_ptr<char[]> source);

    void ReadFile(const char *path, std::shared_ptr<std::string> source);
  }
}

#endif //__FILES_H__