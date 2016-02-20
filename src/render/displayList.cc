/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "render/displayList.h"

ROTOM::DisplayList::DisplayList() {}

ROTOM::DisplayList::~DisplayList() {}

void ROTOM::DisplayList::addCommand(void *command) {
  commandList_.push_back(command);
}

void ROTOM::DisplayList::clearCommandList() {
  commandList_.clear();
}

void ROTOM::DisplayList::runAll() {
  while (commandList_.size() > 0) {
    Command *command = (Command *)(commandList_.at(commandList_.size() - 1));
    command->run();
    commandList_.pop_back();
  }
}