/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_DRAW_OBJECT_H__
#define __COMMAND_DRAW_OBJECT_H__

#include "command.h"
#include "node/drawable.h"
#include "node/light.h"

namespace ROTOM {
  struct CommandDrawObjectData {
    MaterialSettings materialSettings;
    ShaderData shaderData;
    unsigned int geometry_VAO;
    unsigned int geometry_veterCount;
    unsigned int material_texture;
    float material_shininess;
    float material_specularMaterial[4];
    float drawable_modelWorld[16];
  };

  class CommandDrawObject : public Command {
  public:
    CommandDrawObject();
    virtual ~CommandDrawObject();

    //It does what the command should do (it's called from the displayList class)
    void run();

    void setInput(Node *root, Light light, float projectionMatrix[16], float viewMatrix[16]);

  private:
    std::vector<CommandDrawObjectData> commandDrawObjectData_;
    Light light_;
    float projectionMatrix_[16];
    float viewMatrix_[16];

    void setData(Drawable *drawable);

    void setInputChilds(Drawable *drawable);
  };
}

#endif //__COMMAND_DRAW_OBJECT_H__