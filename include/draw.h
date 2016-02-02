/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __DRAW_H__
#define __DRAW_H__

namespace ROTOM {
  //Call this function before start sending drawing commands
  //void DrawBegin();
  
  //Call this function after all drawings are done
  //void DrawEnd();
  
  //Set the color of the stroke
  void DrawSetStrokeColor(const float r, const float g, const float b, const float a = 1.0f);
  
  //Set the color to fill
  void DrawSetFillColor(const float r, const float g, const float b, const float a = 1.0f);

  //Clear the window
  void DrawClear();

  //Set the background color of the window
  void DrawClearColor(const float r, const float g, const float b, const float a = 1.0f);
  
  //Draw a line
  void DrawLine(const float x_start, const float y_start, const float x_end, const float y_end);
  
  //Draw a path
  void DrawPath(const float *pairs_of_points, int num_points);
  
  //Draw a solid path
  void DrawSolidPath(const float *pairs_of_points, int num_points, bool stroke = true);
  
  //Set the text font
  //void DrawSetTextFont(const char *name);
  
  //Set the text size
  //void DrawSetTextSize(const float size);
  
  //Set the text blur size
  //void DrawSetTextBlur(const float blur_radius);
  
  //Draw a text in a position of the window
  //void DrawText(const float x, const float y, const char *text);
}

#endif //__DRAW_H__