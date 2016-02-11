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
  case MyClass_AutoLayering:
    counter.MyClass_AutoLayering++;
    break;
  case MyClass_Branching:
    counter.MyClass_Branching++;
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
  case MyClass_Crossfading:
    counter.MyClass_Crossfading++;
    break;
  case MyClass_DisplayList:
    counter.MyClass_DisplayList++;
    break;
  case MyClass_Drawable:
    counter.MyClass_Drawable++;
    break;
  case MyClass_Geometry:
    counter.MyClass_Geometry++;
    break;
  case MyClass_Layering:
    counter.MyClass_Layering++;
    break;
  case MyClass_Material:
    counter.MyClass_Material++;
    break;
  case MyClass_MaterialSettings:
    counter.MyClass_MaterialSettings++;
    break;
  case MyClass_Node:
    counter.MyClass_Node++;
    break;
  case MyClass_Sound:
    counter.MyClass_Sound++;
    break;
  case MyClass_Task:
    counter.MyClass_Task++;
    break;
  case MyClass_TaskManager:
    counter.MyClass_TaskManager++;
    break;
  case MyClass_TaskCalculateMatrix:
    counter.MyClass_TaskCalculateMatrix++;
    break;
  case MyClass_TrackList:
    counter.MyClass_TrackList++;
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
  case MyClass_AutoLayering:
    counter.MyClass_AutoLayering--;
    break;
  case MyClass_Branching:
    counter.MyClass_Branching--;
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
  case MyClass_Crossfading:
    counter.MyClass_Crossfading--;
    break;
  case MyClass_DisplayList:
    counter.MyClass_DisplayList--;
    break;
  case MyClass_Drawable:
    counter.MyClass_Drawable--;
    break;
  case MyClass_Geometry:
    counter.MyClass_Geometry--;
    break;
  case MyClass_Layering:
    counter.MyClass_Layering--;
    break;
  case MyClass_Material:
    counter.MyClass_Material--;
    break;
  case MyClass_MaterialSettings:
    counter.MyClass_MaterialSettings--;
    break;
  case MyClass_Node:
    counter.MyClass_Node--;
    break;
  case MyClass_Sound:
    counter.MyClass_Sound--;
    break;
  case MyClass_Task:
    counter.MyClass_Task--;
    break;
  case MyClass_TaskManager:
    counter.MyClass_TaskManager--;
    break;
  case MyClass_TaskCalculateMatrix:
    counter.MyClass_TaskCalculateMatrix--;
    break;
  case MyClass_TrackList:
    counter.MyClass_TrackList--;
    break;
  case MyClass_Worker:
    counter.MyClass_Worker--;
    break;
  default:
    printf("ERROR: [Security.cc]\n");
    break;
  }
  if ((counter.MyClass_AutoLayering +
      counter.MyClass_Branching +
      counter.MyClass_Camera +
      counter.MyClass_Chronometer +
      counter.MyClass_Command +
      counter.MyClass_CommandClear +
      counter.MyClass_CommandDrawObject +
      counter.MyClass_Countdown +
      counter.MyClass_Crossfading +
      counter.MyClass_DisplayList +
      counter.MyClass_Drawable +
      counter.MyClass_Geometry +
      counter.MyClass_Layering +
      counter.MyClass_Material +
      counter.MyClass_MaterialSettings +
      counter.MyClass_Node +
      counter.MyClass_Sound +
      counter.MyClass_Task +
      counter.MyClass_TaskManager +
      counter.MyClass_TaskCalculateMatrix +
      counter.MyClass_TrackList +
      counter.MyClass_Worker) == 0) {
    printf("All classes removed\n");
    //system("pause");
  } /*else {
    printf("Not all classes removed\n");
    system("pause");
  }*/
}

int ROTOM::SECURITY::checkSecurityCount(MyClass type) {
  int typeCount = -1;
  switch (type) {
  case MyClass_None:
    typeCount =
      counter.MyClass_AutoLayering +
      counter.MyClass_Branching +
      counter.MyClass_Camera +
      counter.MyClass_Chronometer +
      counter.MyClass_Command +
      counter.MyClass_CommandClear +
      counter.MyClass_CommandDrawObject +
      counter.MyClass_Countdown +
      counter.MyClass_Crossfading +
      counter.MyClass_DisplayList +
      counter.MyClass_Drawable +
      counter.MyClass_Geometry +
      counter.MyClass_Layering +
      counter.MyClass_Material +
      counter.MyClass_MaterialSettings +
      counter.MyClass_Node +
      counter.MyClass_Sound +
      counter.MyClass_Task +
      counter.MyClass_TaskManager +
      counter.MyClass_TaskCalculateMatrix +
      counter.MyClass_TrackList +
      counter.MyClass_Worker;
    if (typeCount == 0) {
      printf("All classes removed\n");
      system("pause");
    } else {
      printf("Not all classes removed\n");
      system("pause");
    }
    break;
  case MyClass_AutoLayering:
    typeCount = counter.MyClass_AutoLayering;
    break;
  case MyClass_Branching:
    typeCount = counter.MyClass_Branching;
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
  case MyClass_Crossfading:
    typeCount = counter.MyClass_Crossfading;
    break;
  case MyClass_DisplayList:
    typeCount = counter.MyClass_DisplayList;
    break;
  case MyClass_Drawable:
    typeCount = counter.MyClass_Drawable;
    break;
  case MyClass_Geometry:
    typeCount = counter.MyClass_Geometry;
    break;
  case MyClass_Layering:
    typeCount = counter.MyClass_Layering;
    break;
  case MyClass_Material:
    typeCount = counter.MyClass_Material;
    break;
  case MyClass_MaterialSettings:
    typeCount = counter.MyClass_MaterialSettings;
    break;
  case MyClass_Node:
    typeCount = counter.MyClass_Node;
    break;
  case MyClass_Sound:
    typeCount = counter.MyClass_Sound;
    break;
  case MyClass_Task:
    typeCount = counter.MyClass_Task;
    break;
  case MyClass_TaskManager:
    typeCount = counter.MyClass_TaskManager;
    break;
  case MyClass_TaskCalculateMatrix:
    typeCount = counter.MyClass_TaskCalculateMatrix;
    break;
  case MyClass_TrackList:
    typeCount = counter.MyClass_TrackList;
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

void ROTOM::SECURITY::drawSecurity() {

}