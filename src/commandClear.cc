/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "commandClear.h"
#include "security.h"
#include "draw.h"

ROTOM::CommandClear::CommandClear() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_CommandClear);
};

ROTOM::CommandClear::~CommandClear() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_CommandClear);
};

void ROTOM::CommandClear::run() {
  DrawClear();
}