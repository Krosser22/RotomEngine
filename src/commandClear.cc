/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "commandClear.h"
#include "security.h"
#include "graphics.h"

ROTOM::CommandClear::CommandClear() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_CommandClear);
};

ROTOM::CommandClear::~CommandClear() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_CommandClear);
};

void ROTOM::CommandClear::run() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //TODO - This is repeated
}