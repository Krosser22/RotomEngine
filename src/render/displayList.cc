/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "render/displayList.h"

ROTOM::DisplayList::DisplayList() {}

ROTOM::DisplayList::~DisplayList() {}

void ROTOM::DisplayList::addCommand(Command *command) {
  commandList_.push_back(command);
}

void ROTOM::DisplayList::clearCommandList() {
  commandList_.clear();
}

void ROTOM::DisplayList::draw() {
  while (commandList_.size() > 0) {
    commandList_.at(commandList_.size() - 1)->run();
    commandList_.pop_back();
  }
}