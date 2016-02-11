/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "materialSettings.h"

#include "graphics.h"
#include "security.h"

ROTOM::MaterialSettings::MaterialSettings() {
  SECURITY::addSecurityCount(SECURITY::MyClass_MaterialSettings);
}

ROTOM::MaterialSettings::~MaterialSettings() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_MaterialSettings);
}