/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "security.h"

#include <windows.h> //<-- DO NOT REMOVE THIS INCLUDE

void ROTOM::SECURITY::addSecurityCount(MyClass type) {
  switch (type) {
  case MyClass_None:
    //counter.MyClass_None++;
    break;
  case MyClass_Camera:
    counter.MyClass_Camera++;
    break;
  case MyClass_Chronometer:
    counter.MyClass_Chronometer++;
    break;
  case MyClass_Command:
    counter.MyClass_Command++;
    break;
  case MyClass_CommandClear:
    counter.MyClass_CommandClear++;
    break;
  case MyClass_CommandDrawObject:
    counter.MyClass_CommandDrawObject++;
    break;
  case MyClass_Countdown:
    counter.MyClass_Countdown++;
    break;
  case MyClass_Drawable:
    counter.MyClass_Drawable++;
    break;
  case MyClass_Geometry:
    counter.MyClass_Geometry++;
    break;
  case MyClass_Material:
    counter.MyClass_Material++;
    break;
  case MyClass_Node:
    counter.MyClass_Node++;
    break;
  case MyClass_Task:
    counter.MyClass_Task++;
    break;
  case MyClass_TaskManager:
    counter.MyClass_TaskManager++;
    break;
  case MyClass_TaskCalculateModel:
    counter.MyClass_TaskCalculateModel++;
    break;
  case MyClass_Worker:
    counter.MyClass_Worker++;
    break;
  default:
    printf("ERROR: [Security.cc]\n");
    break;
  }
}

void ROTOM::SECURITY::removeSecurityCount(MyClass type) {
  switch (type) {
  case MyClass_None:
    //counter.MyClass_None--;
    break;
  case MyClass_Camera:
    counter.MyClass_Camera--;
    break;
  case MyClass_Chronometer:
    counter.MyClass_Chronometer--;
    break;
  case MyClass_Command:
    counter.MyClass_Command--;
    break;
  case MyClass_CommandClear:
    counter.MyClass_CommandClear--;
    break;
  case MyClass_CommandDrawObject:
    counter.MyClass_CommandDrawObject--;
    break;
  case MyClass_Countdown:
    counter.MyClass_Countdown--;
    break;
  case MyClass_Drawable:
    counter.MyClass_Drawable--;
    break;
  case MyClass_Geometry:
    counter.MyClass_Geometry--;
    break;
  case MyClass_Material:
    counter.MyClass_Material--;
    break;
  case MyClass_Node:
    counter.MyClass_Node--;
    break;
  case MyClass_Task:
    counter.MyClass_Task--;
    break;
  case MyClass_TaskManager:
    counter.MyClass_TaskManager--;
    break;
  case MyClass_TaskCalculateModel:
    counter.MyClass_TaskCalculateModel--;
    break;
  case MyClass_Worker:
    counter.MyClass_Worker--;
    break;
  default:
    printf("ERROR: [Security.cc]\n");
    break;
  }
  /*if ((counter.MyClass_Camera +
      counter.MyClass_Chronometer +
      counter.MyClass_Command +
      counter.MyClass_CommandClear +
      counter.MyClass_CommandDrawObject +
      counter.MyClass_Countdown +
      counter.MyClass_Drawable +
      counter.MyClass_Geometry +
      counter.MyClass_Material +
      counter.MyClass_Node +
      counter.MyClass_Task +
      counter.MyClass_TaskManager +
      counter.MyClass_TaskCalculateModel +
      counter.MyClass_Worker) == 0) {
    printf("All clear\n");
    //system("pause");
  } else {
    printf("");
  }*/
}

int ROTOM::SECURITY::checkSecurityCount(MyClass type) {
  int typeCount = -1;
  switch (type) {
  case MyClass_None:
    typeCount =
      counter.MyClass_Camera +
      counter.MyClass_Chronometer +
      counter.MyClass_Command +
      counter.MyClass_CommandClear +
      counter.MyClass_CommandDrawObject +
      counter.MyClass_Countdown +
      counter.MyClass_Drawable +
      counter.MyClass_Geometry +
      counter.MyClass_Material +
      counter.MyClass_Node +
      counter.MyClass_Task +
      counter.MyClass_TaskManager +
      counter.MyClass_TaskCalculateModel +
      counter.MyClass_Worker;
    if (typeCount == 0) {
      system("pause");
    }
    break;
  case MyClass_Camera:
    typeCount = counter.MyClass_Camera;
    break;
  case MyClass_Chronometer:
    typeCount = counter.MyClass_Chronometer;
    break;
  case MyClass_Command:
    typeCount = counter.MyClass_Command;
    break;
  case MyClass_CommandClear:
    typeCount = counter.MyClass_CommandClear;
    break;
  case MyClass_CommandDrawObject:
    typeCount = counter.MyClass_CommandDrawObject;
    break;
  case MyClass_Countdown:
    typeCount = counter.MyClass_Countdown;
    break;
  case MyClass_Drawable:
    typeCount = counter.MyClass_Drawable;
    break;
  case MyClass_Geometry:
    typeCount = counter.MyClass_Geometry;
    break;
  case MyClass_Material:
    typeCount = counter.MyClass_Material;
    break;
  case MyClass_Node:
    typeCount = counter.MyClass_Node;
    break;
  case MyClass_Task:
    typeCount = counter.MyClass_Task;
    break;
  case MyClass_TaskManager:
    typeCount = counter.MyClass_TaskManager;
    break;
  case MyClass_TaskCalculateModel:
    typeCount = counter.MyClass_TaskCalculateModel;
    break;
  case MyClass_Worker:
    typeCount = counter.MyClass_Worker;
    break;
  default:
    printf("ERROR: [Security.cc]\n");
    break;
  }
  return typeCount;
}

void drawSecurity();