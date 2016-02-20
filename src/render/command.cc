/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "render/command.h"

ROTOM::Command::Command() {}

ROTOM::Command::~Command() {}

void *ROTOM::Command::get() {
  return (void *)this;
}