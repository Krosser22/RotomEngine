/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "time.h"

#include "gl.h"
#include "security.h"

float ROTOM::TIME::appTime() {
  return (float)glfwGetTime();
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
  timeToEnd_ = ROTOM::TIME::appTime() + timeAmount;
}

bool ROTOM::TIME::Countdown::finish() {
  return (ROTOM::TIME::appTime() > timeToEnd_);
}

ROTOM::TIME::Chronometer::Chronometer() {
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Chronometer);
};

ROTOM::TIME::Chronometer::~Chronometer() {
  ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Chronometer);
};

void ROTOM::TIME::Chronometer::start() {
  timeWhenStarted_ = ROTOM::TIME::appTime();
}

const double ROTOM::TIME::Chronometer::end() {
  return (ROTOM::TIME::appTime() - timeWhenStarted_);
}