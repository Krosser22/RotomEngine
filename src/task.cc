/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "task.h"
#include "security.h"

ROTOM::Task::Task() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Task);
}

ROTOM::Task::~Task() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_Task);
}