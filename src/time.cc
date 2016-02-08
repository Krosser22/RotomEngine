/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "time.h"

#include "graphics.h"
#include "security.h"

float ROTOM::TIME::appTime() {
  return GRAPHICS::getTime();
}

ROTOM::TIME::Countdown::Countdown() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Countdown);
};

ROTOM::TIME::Countdown::Countdown(const double timeAmount) {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Countdown);
  startTimer(timeAmount);
}

ROTOM::TIME::Countdown::~Countdown() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_Countdown);
};

void ROTOM::TIME::Countdown::startTimer(const double timeAmount) {
  timeToEnd_ = TIME::appTime() + timeAmount;
}

bool ROTOM::TIME::Countdown::finish() {
  return (TIME::appTime() > timeToEnd_);
}

ROTOM::TIME::Chronometer::Chronometer() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Chronometer);
};

ROTOM::TIME::Chronometer::~Chronometer() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_Chronometer);
};

void ROTOM::TIME::Chronometer::start() {
  timeWhenStarted_ = TIME::appTime();
}

const double ROTOM::TIME::Chronometer::end() {
  return (TIME::appTime() - timeWhenStarted_);
}