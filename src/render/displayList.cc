/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/displayList.h"

ROTOM::DisplayList::DisplayList() {}

ROTOM::DisplayList::~DisplayList() {}

void ROTOM::DisplayList::addCommand(Command *command) {
  commandList_.push_back(command);
}

void ROTOM::DisplayList::draw() {
  for (unsigned int i = 0; i < commandList_.size(); ++i) {
    commandList_.at(i)->run();
  }
  commandList_.clear();
}