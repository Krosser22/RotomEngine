/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/time.h"
#include "render/graphics.h"

float ROTOM::TIME::appTime() {
  return GRAPHICS::getTime();
}

ROTOM::TIME::Countdown::Countdown() {}

ROTOM::TIME::Countdown::Countdown(const double timeAmount) {
  startTimer(timeAmount);
}

ROTOM::TIME::Countdown::~Countdown() {}

void ROTOM::TIME::Countdown::startTimer(const double timeAmount) {
  timeToEnd_ = TIME::appTime() + timeAmount;
}

bool ROTOM::TIME::Countdown::finish() {
  return (TIME::appTime() > timeToEnd_);
}

ROTOM::TIME::Chronometer::Chronometer() {}

ROTOM::TIME::Chronometer::~Chronometer() {}

void ROTOM::TIME::Chronometer::start() {
  timeWhenStarted_ = TIME::appTime();
}

const double ROTOM::TIME::Chronometer::end() {
  return (TIME::appTime() - timeWhenStarted_);
}