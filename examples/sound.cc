/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "camera.h"
#include "drawable.h"
#include "geometry.h"
#include "imgui.h"
#include "sound.h"
#include "taskManager.h"
#include "time.h"
#include "window.h"

enum Playing {
  Playing_None,
  Playing_Sound,
  Playing_TrackList,
  Playing_AutoLayering,
  Playing_Layering,
  Playing_Branching
} playing;

static const float imgui_width = 150.0f;
static const float imgui_height = 45.0f;
static const ImVec2 sizeOfBlocks(imgui_width, imgui_height * 2);
static const ImVec2 sizeOfElements(imgui_width, imgui_height);

std::vector<ROTOM::SOUND::Sound *> sounds;
ROTOM::SOUND::TrackList trackList;
ROTOM::SOUND::AutoLayering autoLayering;
ROTOM::SOUND::Layering layering;
ROTOM::SOUND::Branching branching;

void changePlaying(Playing newPlaying) {
  switch (playing)
  {
    case Playing_None:
      break;
    case Playing_Sound:
      for (unsigned int i = 0; i < sounds.size(); ++i) {
        sounds.at(i)->stop();
      }
      break;
    case Playing_TrackList:
      trackList.stop();
      break;
    case Playing_AutoLayering:
      autoLayering.stop();
      break;
    case Playing_Layering:
      layering.stop();
      break;
    case Playing_Branching:
      branching.stop();
      break;
    default:
      break;
  }
  playing = newPlaying;
}

void imgui() {
  ImGui::Begin("Sound Scene");
  {
    ImGui::Text("Daniel Laserna Condado");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  }
  ImGui::End();

  ImGui::Begin("Input");
  {
    ImGui::BeginChildFrame(1, ImVec2(imgui_width, imgui_height * 4));
    {
      ImGui::Text("Sounds");
      if (playing == Playing_Sound) {
        for (unsigned int i = 0; i < sounds.size(); ++i) {
          ImGui::BeginChildFrame(i, sizeOfElements);
          {
            if (sounds.at(i)->isPlaying()) {
              if (ImGui::Button("Pause")) {
                sounds.at(i)->pause();
              }
              if (ImGui::Button("Stop")) {
                sounds.at(i)->stop();
              }
            } else if (ImGui::Button("Play")) {
              sounds.at(i)->play();
              sounds.at(i)->setGain(1.0f);
            }
          }
          ImGui::EndChildFrame();
        }
      } else if (ImGui::Button("Play Sound")) {
        changePlaying(Playing_Sound);
      }
    }
    ImGui::EndChildFrame();

    ImGui::BeginChildFrame(2, sizeOfBlocks);
    {
      ImGui::Text("TrackList");
      if (playing == Playing_TrackList) {
        trackList.update();
        if (ImGui::Button("Play")) {
          trackList.play();
        }
        if (ImGui::Button("Stop")) {
          trackList.stop();
        }
      } else if (ImGui::Button("Play TrackList")) {
        changePlaying(Playing_TrackList);
      }
    }
    ImGui::EndChildFrame();

    ImGui::BeginChildFrame(3, sizeOfBlocks);
    {
      ImGui::Text("AutoLayering");
      if (playing == Playing_AutoLayering) {
        autoLayering.update();
        if (ImGui::Button("Play")) {
          autoLayering.play();
        }
        if (ImGui::Button("Stop")) {
          autoLayering.stop();
        }
      } else if (ImGui::Button("Play AutoLayering")) {
        changePlaying(Playing_AutoLayering);
      }
    }
    ImGui::EndChildFrame();

    ImGui::BeginChildFrame(4, sizeOfBlocks);
    {
      ImGui::Text("Layering");
      if (playing == Playing_Layering) {
        layering.update();
        if (ImGui::Button("Increase")) {
          layering.increase();
        }
        if (ImGui::Button("Decrease")) {
          layering.decrease();
        }
      } else if (ImGui::Button("Play Layering")) {
        changePlaying(Playing_Layering);
      }
    }
    ImGui::EndChildFrame();

    ImGui::BeginChildFrame(5, sizeOfBlocks);
    {
      ImGui::Text("Branching");
      if (playing == Playing_Branching) {
        branching.update();
        if (ImGui::Button("Move to A")) {
          branching.changeBranch(ROTOM::SOUND::Branch::Branch_A);
        }
        if (ImGui::Button("Move to B")) {
          branching.changeBranch(ROTOM::SOUND::Branch::Branch_B);
        }
        if (ImGui::Button("Move to C")) {
          branching.changeBranch(ROTOM::SOUND::Branch::Branch_C);
        }
      } else if (ImGui::Button("Play Branching")) {
        changePlaying(Playing_Branching);
      }
    }
    ImGui::EndChildFrame();
  }
  ImGui::End();
}

void run_scene_sound() {
  //WindowInit(1280, 720);

  ROTOM::Camera camera;
  camera.setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  camera.setupPerspective(45.0f, (float)ROTOM::WindowWidth() / (float)ROTOM::WindowHeight(), 0.1f, 100.0f);
  camera.setPosition(0.0f, 0.0f, 0.0f);

  //Sound
  sounds.push_back(new ROTOM::SOUND::Sound("sound/Layering/LAYER_C_0.ogg"));
  sounds.push_back(new ROTOM::SOUND::Sound("sound/Layering/LAYER_C_1.ogg"));
  sounds.push_back(new ROTOM::SOUND::Sound("sound/Layering/LAYER_C_2.ogg"));
  trackList.addSound(sounds.at(0));
  trackList.addSound(sounds.at(1));
  trackList.addSound(sounds.at(2));
  autoLayering.addSound(sounds.at(0));
  autoLayering.addSound(sounds.at(1));
  autoLayering.addSound(sounds.at(2));
  layering.addSound(sounds.at(0));
  layering.addSound(sounds.at(1));
  layering.addSound(sounds.at(2));
  branching.addSound(new ROTOM::SOUND::Sound("sound/Branching/Branching_A_0.ogg"));
  branching.addSound(new ROTOM::SOUND::Sound("sound/Branching/Branching_B_0.ogg"));
  branching.addSound(new ROTOM::SOUND::Sound("sound/Branching/Branching_B_1.ogg"));
  branching.setTransitionSound(new ROTOM::SOUND::Sound("sound/Branching/Branching_Transition.ogg"));

  float sin_time = 0.0f;
  while (ROTOM::WindowIsOpened()) {
    //draw 3D
    camera.doRender();
    //...

    //draw 2D (IMGUI)
    imgui();
    //...
  }
}
