/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_DRAW_OBJECT_H__
#define __COMMAND_DRAW_OBJECT_H__

#include "command.h"
#include "drawable.h"
#include "light.h"

namespace ROTOM {
  class CommandDrawObject : public Command {
  public:
    CommandDrawObject();
    virtual ~CommandDrawObject();

    //It does what the command should do (it's called from the displayList class)
    void run();

    void setRoot(Node *root);

    void setProjectionMatrix(float *projectionMatrix);

    void setViewMatrix(float *viewMatrix);

    void setLight(Light *light);

  private:
    Node *root_;
    float *projectionMatrix_;
    float *viewMatrix_;
    Light *light_;

    void draw(Drawable *drawable);

    void drawChilds(Drawable *drawable);
  };
}

#endif //__COMMAND_DRAW_OBJECT_H__