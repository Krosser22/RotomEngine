/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/input.h"
#include "imgui.h"
#include <stdio.h>

ImGuiIO& io = ImGui::GetIO();
ImGuiIO ioFrameBefore;

void ROTOM::INPUT::Update() {
  ioFrameBefore = io;
}

bool ROTOM::INPUT::IsKeyDown(unsigned char key) {
  return (io.KeysDown[(unsigned int)key]);
}

bool ROTOM::INPUT::IsKeyPressed(unsigned char key) {
  bool before = ioFrameBefore.KeysDown[(unsigned int)key];
  bool now = io.KeysDown[(unsigned int)key];
  return (!before && now);
}

bool ROTOM::INPUT::IsKeyReleased(unsigned char key) {
  bool before = ioFrameBefore.KeysDown[(unsigned int)key];
  bool now = io.KeysDown[(unsigned int)key];
  return (before && !now);
}

bool ROTOM::INPUT::IsMouseDown(unsigned char button) {
  return (io.MouseDown[(unsigned int)button]);
}

bool ROTOM::INPUT::IsMousePressed(unsigned char button) {
  return (io.MouseClicked[(unsigned int)button]);
}

bool ROTOM::INPUT::IsMouseReleased(unsigned char button) {
  return (io.MouseReleased[(unsigned int)button]);
}

float ROTOM::INPUT::MouseWheel() {
  return (io.MouseWheel);
}

float ROTOM::INPUT::MousePositionX() {
  return (io.MousePos.x);
}

float ROTOM::INPUT::MousePositionY() {
  return (io.MousePos.y);
}