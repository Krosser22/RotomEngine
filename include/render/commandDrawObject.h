/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_DRAW_OBJECT_H__
#define __COMMAND_DRAW_OBJECT_H__

#include "command.h"
#include "node/geometry.h"
#include "node/directionalLight.h"
#include "node/spotLight.h"
#include "render/renderTarget.h"

namespace ROTOM {
  struct CommandDrawObjectData {
    bool visible;
    bool shadows;
    FramebufferData framebufferData;
    MaterialSettings materialSettings;
    MaterialData materialData;
    ShaderData shaderData;
    unsigned int geometry_VAO;
    unsigned int geometry_veterCount;
    unsigned int material_texture;
    float drawable_worldMatrix[16];
  };

  class CommandDrawObject : public Command {
  public:
    CommandDrawObject();
    virtual ~CommandDrawObject();

    void run();
    
    void setInput(std::shared_ptr<Node> root, std::vector<std::shared_ptr<DirectionalLight>> directionalLights, std::vector<std::shared_ptr<SpotLight>> spotLights, float projectionMatrix[16], float viewMatrix[16], float *viewPosition);

  private:
    std::vector<CommandDrawObjectData> commandDrawObjectData_;
    std::vector<std::shared_ptr<DirectionalLight>> directionalLights_;
    std::vector<std::shared_ptr<SpotLight>> spotLights_;
    float projectionMatrix_[16];
    float viewMatrix_[16];
    float viewPosition_[3];

    void setData(Drawable *node);

    void setInputChilds(Drawable *drawable);
  };
}

#endif //__COMMAND_DRAW_OBJECT_H__