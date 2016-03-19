/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
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

    std::string ReadFile(const char *path);
  }
}

#endif //__FILES_H__