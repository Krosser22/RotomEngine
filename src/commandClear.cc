/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "commandClear.h"
#include "security.h"
#include "draw.h"

ROTOM::CommandClear::CommandClear() {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_CommandClear);
};

ROTOM::CommandClear::~CommandClear() {
  ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass::MyClass_CommandClear);
};

void ROTOM::CommandClear::run() {
  ROTOM::DrawClear();
}