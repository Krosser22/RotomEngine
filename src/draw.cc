/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "draw.h"
#include "gl.h"
#include "window.h"

static float strokeColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float fillColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

/*void ROTOM::DrawBegin() {
  glBegin(mode);
}

void ROTOM::DrawEnd() {
  glEnd();
}*/

void ROTOM::DrawSetStrokeColor(const float r, const float g, const float b, const float a) {
  strokeColor[0] = r;
  strokeColor[1] = g;
  strokeColor[2] = b;
  strokeColor[3] = a;
}

void ROTOM::DrawSetFillColor(const float r, const float g, const float b, const float a) {
  fillColor[0] = r;
  fillColor[1] = g;
  fillColor[2] = b;
  fillColor[3] = a;
}

void ROTOM::DrawClear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ROTOM::DrawClearColor(const float r, const float g, const float b, const float a) {
  glClearColor(r, g, b, a);
}

void ROTOM::DrawLine(const float x_start, const float y_start, const float x_end, const float y_end) {
  glBegin(GL_LINES);
  glColor4f(strokeColor[0], strokeColor[1], strokeColor[2], strokeColor[3]);
  glVertex2f((x_start * 2.0f / WindowWidth()) - 1.0f, (y_start * 2.0f / WindowHeight()) - 1.0f);
  glColor4f(strokeColor[0], strokeColor[1], strokeColor[2], strokeColor[3]);
  glVertex2f((x_end * 2.0f / WindowWidth()) - 1.0f, (y_end * 2.0f / WindowHeight()) - 1.0f);
  glEnd();
}

void ROTOM::DrawPath(const float *pairs_of_points, int num_points) {
  if(num_points > 1) {
    glBegin(GL_LINES);
    for (int i = 0; i < (num_points - 1); ++i) {
      glColor4f(strokeColor[0], strokeColor[1], strokeColor[2], strokeColor[3]);
      glVertex2f((pairs_of_points[i * 2] * 2.0f / WindowWidth()) - 1.0f, (pairs_of_points[(i * 2) + 1] * 2.0f / WindowHeight()) - 1.0f);
      glColor4f(strokeColor[0], strokeColor[1], strokeColor[2], strokeColor[3]);
      glVertex2f((pairs_of_points[(i + 1) * 2] * 2.0f / WindowWidth()) - 1.0f, (pairs_of_points[((i + 1) * 2) + 1] * 2.0f / WindowHeight()) - 1.0f);
    }
    glEnd();
  }
}

void ROTOM::DrawSolidPath(const float *pairs_of_points, int num_points, bool stroke) {
  if(num_points > 1) {
    if (stroke) {
      glBegin(GL_LINES);
      for (int i = 0; i < (num_points - 1); ++i) {
        glColor4f(strokeColor[0], strokeColor[1], strokeColor[2], strokeColor[3]);
        glVertex2f((pairs_of_points[i * 2] * 2.0f / WindowWidth()) - 1.0f, (pairs_of_points[(i * 2) + 1] * 2.0f / WindowHeight()) - 1.0f);
        glColor4f(strokeColor[0], strokeColor[1], strokeColor[2], strokeColor[3]);
        glVertex2f((pairs_of_points[(i + 1) * 2] * 2.0f / WindowWidth()) - 1.0f, (pairs_of_points[((i + 1) * 2) + 1] * 2.0f / WindowHeight()) - 1.0f);
      }
      glEnd();
    }
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_points; ++i) {
      glColor4f(fillColor[0], fillColor[1], fillColor[2], fillColor[3]);
      glVertex2f((pairs_of_points[i * 2] * 2.0f / WindowWidth()) - 1.0f, (pairs_of_points[(i * 2) + 1] * 2.0f / WindowHeight()) - 1.0f);
      glColor4f(fillColor[0], fillColor[1], fillColor[2], fillColor[3]);
      glVertex2f((pairs_of_points[(i + 1) * 2] * 2.0f / WindowWidth()) - 1.0f, (pairs_of_points[((i + 1) * 2) + 1] * 2.0f / WindowHeight()) - 1.0f);
    }
    glEnd();
  }
}

/*void ROTOM::DrawSetTextFont(const char *name) {
  
}

void ROTOM::DrawSetTextSize(const float size) {
  
}

void ROTOM::DrawSetTextBlur(const float blur_radius) {
  
}

void ROTOM::DrawText(const float x, const float y, const char *text) {
  
}*/