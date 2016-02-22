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
  struct CommandDrawObjectData {
    MaterialSettings materialSettings;
    unsigned int geometry_VAO;
    unsigned int geometry_veterCount;
    float drawable_modelWorld[16];
    ShaderData shaderData;
    float material_shininess_;
    float material_specularMaterial_[4];
  };

  class CommandDrawObject : public Command {
  public:
    CommandDrawObject();
    virtual ~CommandDrawObject();

    std::vector<CommandDrawObjectData> commandDrawObjectData_;

    //It does what the command should do (it's called from the displayList class)
    void run();

    void setInput(Node *root, Light light, float projectionMatrix[16], float viewMatrix[16]);

  private:
    Node *root_; -----------eliminar esta variable y utilizar en su lugar la variable dataaaa
    Light light_;
    float projectionMatrix_[16];
    float viewMatrix_[16];

    void draw(Node *node);

    void drawChilds(Node *node);

    void setInput(Node *node);

    void setInputChilds(Node *node);
  };
}

#endif //__COMMAND_DRAW_OBJECT_H__