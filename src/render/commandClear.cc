/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/commandClear.h"
#include "render/graphics.h"

ROTOM::CommandClear::CommandClear() {}

ROTOM::CommandClear::~CommandClear() {}

void ROTOM::CommandClear::run() {
  GRAPHICS::clearScreen();
}