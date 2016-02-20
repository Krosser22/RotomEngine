/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "render/commandClear.h"
#include "render/graphics.h"

ROTOM::CommandClear::CommandClear() {}

ROTOM::CommandClear::~CommandClear() {}

void ROTOM::CommandClear::run() {
  GRAPHICS::clearScreen();
}