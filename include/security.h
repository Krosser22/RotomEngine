/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SECURITY_H__
#define __SECURITY_H__

//#include "ref_ptr.h"
//#include "scoped_array.h"

#include <stdio.h>

namespace ROTOM {
  namespace SECURITY {
    static enum MyClass {
      MyClass_None = 0,
      MyClass_AutoLayering,
      MyClass_Branching,
      MyClass_Camera,
      MyClass_Chronometer,
      MyClass_Command,
      MyClass_CommandClear,
      MyClass_CommandDrawObject,
      MyClass_Countdown,
      MyClass_Crossfading,
      MyClass_DisplayList,
      MyClass_Drawable,
      MyClass_Geometry,
      MyClass_Layering,
      MyClass_Material,
      MyClass_Node,
      MyClass_Sound,
      MyClass_Task,
      MyClass_TaskManager,
      MyClass_TaskCalculateMatrix,
      MyClass_TrackList,
      MyClass_Worker
    };

    struct Counter {
      //int MyClass_None;
      int MyClass_AutoLayering;
      int MyClass_Branching;
      int MyClass_Camera;
      int MyClass_Chronometer;
      int MyClass_Command;
      int MyClass_CommandClear;
      int MyClass_CommandDrawObject;
      int MyClass_Countdown;
      int MyClass_Crossfading;
      int MyClass_DisplayList;
      int MyClass_Drawable;
      int MyClass_Geometry;
      int MyClass_Layering;
      int MyClass_Material;
      int MyClass_Node;
      int MyClass_Sound;
      int MyClass_Task;
      int MyClass_TaskManager;
      int MyClass_TaskCalculateMatrix;
      int MyClass_TrackList;
      int MyClass_Worker;
    };

    static Counter counter;

    void addSecurityCount(MyClass type = MyClass_None);

    void removeSecurityCount(MyClass type = MyClass_None);

    int checkSecurityCount(MyClass type = MyClass_None);

    void drawSecurity();
  }
}

#endif //__SECURITY_H__