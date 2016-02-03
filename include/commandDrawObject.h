/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_DRAW_OBJECT_H__
#define __COMMAND_DRAW_OBJECT_H__

#include "command.h"
#include "drawable.h"

namespace ROTOM {
  class CommandDrawObject : public Command {
  public:
    CommandDrawObject();
    virtual ~CommandDrawObject();

    //TODO - The shader of this isnot working
    float lightPosition_[3];
    float lightColor_[3];
    float shininess_;
    float specularIntensity_[4];
    float specularMaterial_[4];

    //It does what the command should do (it's called from the displayList class)
    void run();

    void setRoot(Node *root);

    void setProjectionMatrix(float *projectionMatrix);

  private:
    float *projectionMatrix_;

    Node *root_;

    void draw(Drawable *drawable);

    void drawChilds(Drawable *drawable);
  };
}

#endif //__COMMAND_DRAW_OBJECT_H__