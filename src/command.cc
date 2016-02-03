/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "command.h"
#include "security.h"

ROTOM::Command::Command() {
  SECURITY::addSecurityCount(SECURITY::MyClass_Command);
};

ROTOM::Command::~Command() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_Command);
};

void *ROTOM::Command::get() {
  return (void *)this;
}