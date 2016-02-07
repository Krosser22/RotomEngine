/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TEXT_H__
#define __TEXT_H__

#include <memory>
#include <string>

namespace ROTOM {
  void read_file(const char* file_name, std::shared_ptr<std::string> source);
}
#endif __TEXT_H__