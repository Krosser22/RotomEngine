/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "command.h"
#include "security.h"

ROTOM::Command::Command() {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass_Command);
};

ROTOM::Command::~Command() {
  ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass_Command);
};

void *ROTOM::Command::get() {
  return (void *)this;
}