/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/graphics.h"
#include <imgui.h>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#ifdef _MSC_VER
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

struct GLFWwindow;

IMGUI_API bool ImGui_Init(GLFWwindow* window, bool install_callbacks);
IMGUI_API void ImGui_Shutdown();
IMGUI_API void ImGui_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void ImGui_InvalidateDeviceObjects();
IMGUI_API bool ImGui_CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
IMGUI_API void ImGui_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
IMGUI_API void ImGui_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
IMGUI_API void ImGui_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
IMGUI_API void ImGui_CharCallback(GLFWwindow* window, unsigned int c);

IMGUI_API void ImGui_RenderDrawLists(ImDrawData* draw_data);

// Data
static GLFWwindow  *window = nullptr;
static double       g_Time = 0.0f;
static bool         g_MousePressed[3] = { false, false, false };
static float        g_MouseWheel = 0.0f;
static unsigned int g_FontTexture = 0;
static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

//Texture
static int textureID = 0;
ROTOM::RenderTarget actualRenderTarget;

static void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

void ImGui_RenderDrawLists(ImDrawData* draw_data) {
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_SCISSOR_TEST);
  glActiveTexture(GL_TEXTURE0);

  // Handle cases of screen coordinates != from framebuffer coordinates (e.g. retina displays)
  ImGuiIO& io = ImGui::GetIO();
  float fb_height = io.DisplaySize.y * io.DisplayFramebufferScale.y;
  draw_data->ScaleClipRects(io.DisplayFramebufferScale);

  // Setup viewport, orthographic projection matrix
  const float ortho_projection[4][4] =
  {
    { 2.0f / io.DisplaySize.x, 0.0f, 0.0f, 0.0f },
    { 0.0f, 2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
    { 0.0f, 0.0f, -1.0f, 0.0f },
    { -1.0f, 1.0f, 0.0f, 1.0f },
  };
  glUseProgram(g_ShaderHandle);
  glUniform1i(g_AttribLocationTex, 0);
  glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
  glBindVertexArray(g_VaoHandle);

  glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
  for (int n = 0; n < draw_data->CmdListsCount; n++) {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    const ImDrawIdx* idx_buffer_offset = 0;

    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), (GLvoid*)&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), (GLvoid*)&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

    for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++) {
      if (pcmd->UserCallback) {
        pcmd->UserCallback(cmd_list, pcmd);
      } else {
        glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
        //glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
        glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
      }
      idx_buffer_offset += pcmd->ElemCount;
    }
  }

  // Restore modified GL state
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_SCISSOR_TEST);
}

static const char* ImGui_GetClipboardText() {
  return glfwGetClipboardString(window);
}

static void ImGui_SetClipboardText(const char* text) {
  glfwSetClipboardString(window, text);
}

void ImGui_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS && button >= 0 && button < 3) {
    g_MousePressed[button] = true;
  }
}

void ImGui_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  g_MouseWheel += (float)yoffset; // Use fractional mouse wheel, 1.0 unit 5 lines.
}

void ImGui_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  ImGuiIO& io = ImGui::GetIO();
  if (action == GLFW_PRESS) {
    io.KeysDown[key] = true;
  }

  if (action == GLFW_RELEASE) {
    io.KeysDown[key] = false;
  }

  /////ESCAPE FOR EXIT
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  (void)mods; // Modifiers are not reliable across systems
  io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
}

void ImGui_CharCallback(GLFWwindow* window, unsigned int c) {
  ImGuiIO& io = ImGui::GetIO();
  if (c > 0 && c < 0x10000)
    io.AddInputCharacter((unsigned short)c);
}

void ImGui_CreateFontsTexture() {
  ImGuiIO& io = ImGui::GetIO();

  // Build texture atlas
  unsigned char* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits for OpenGL3 demo because it is more likely to be compatible with user's existing shader.

  // Create OpenGL texture
  glGenTextures(1, &g_FontTexture);
  glBindTexture(GL_TEXTURE_2D, g_FontTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  // Store our identifier
  io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

  // Cleanup (don't clear the input data if you want to append new fonts later)
  io.Fonts->ClearInputData();
  io.Fonts->ClearTexData();
}

bool ImGui_CreateDeviceObjects() {
  // Backup GL state
  GLint last_texture, last_array_buffer, last_vertex_array;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

  const GLchar *vertex_shader =
    "#version 330\n"
    "uniform mat4 ProjMtx;\n"
    "in vec2 Position;\n"
    "in vec2 UV;\n"
    "in vec4 Color;\n"
    "out vec2 Frag_UV;\n"
    "out vec4 Frag_Color;\n"
    "void main()\n"
    "{\n"
    "	Frag_UV = UV;\n"
    "	Frag_Color = Color;\n"
    "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
    "}\n";

  const GLchar* fragment_shader =
    "#version 330\n"
    "uniform sampler2D Texture;\n"
    "in vec2 Frag_UV;\n"
    "in vec4 Frag_Color;\n"
    "out vec4 Out_Color;\n"
    "void main()\n"
    "{\n"
    "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
    "}\n";

  g_ShaderHandle = glCreateProgram();
  g_VertHandle = glCreateShader(GL_VERTEX_SHADER);
  g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(g_VertHandle, 1, &vertex_shader, 0);
  glShaderSource(g_FragHandle, 1, &fragment_shader, 0);
  glCompileShader(g_VertHandle);
  glCompileShader(g_FragHandle);
  glAttachShader(g_ShaderHandle, g_VertHandle);
  glAttachShader(g_ShaderHandle, g_FragHandle);
  glLinkProgram(g_ShaderHandle);

  g_AttribLocationTex = glGetUniformLocation(g_ShaderHandle, "Texture");
  g_AttribLocationProjMtx = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
  g_AttribLocationPosition = glGetAttribLocation(g_ShaderHandle, "Position");
  g_AttribLocationUV = glGetAttribLocation(g_ShaderHandle, "UV");
  g_AttribLocationColor = glGetAttribLocation(g_ShaderHandle, "Color");

  glGenBuffers(1, &g_VboHandle);
  glGenBuffers(1, &g_ElementsHandle);

  glGenVertexArrays(1, &g_VaoHandle);
  glBindVertexArray(g_VaoHandle);
  glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
  glEnableVertexAttribArray(g_AttribLocationPosition);
  glEnableVertexAttribArray(g_AttribLocationUV);
  glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
  glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
  glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
  glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

  ImGui_CreateFontsTexture();

  // Restore modified GL state
  glBindTexture(GL_TEXTURE_2D, last_texture);
  glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
  glBindVertexArray(last_vertex_array);

  return true;
}

void ImGui_InvalidateDeviceObjects() {
  if (g_VaoHandle) glDeleteVertexArrays(1, &g_VaoHandle);
  if (g_VboHandle) glDeleteBuffers(1, &g_VboHandle);
  if (g_ElementsHandle) glDeleteBuffers(1, &g_ElementsHandle);
  g_VaoHandle = g_VboHandle = g_ElementsHandle = 0;

  glDetachShader(g_ShaderHandle, g_VertHandle);
  glDeleteShader(g_VertHandle);
  g_VertHandle = 0;

  glDetachShader(g_ShaderHandle, g_FragHandle);
  glDeleteShader(g_FragHandle);
  g_FragHandle = 0;

  glDeleteProgram(g_ShaderHandle);
  g_ShaderHandle = 0;

  if (g_FontTexture) {
    glDeleteTextures(1, &g_FontTexture);
    ImGui::GetIO().Fonts->TexID = 0;
    g_FontTexture = 0;
  }
}

bool ImGui_Init(GLFWwindow* window, bool install_callbacks) {
  ImGuiIO& io = ImGui::GetIO();
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;                         // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  io.RenderDrawListsFn = ImGui_RenderDrawLists;       // Alternatively you can set this to nullptr and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
  io.SetClipboardTextFn = ImGui_SetClipboardText;
  io.GetClipboardTextFn = ImGui_GetClipboardText;
#ifdef _WIN32
  io.ImeWindowHandle = glfwGetWin32Window(window);
#endif

  glfwSetMouseButtonCallback(window, ImGui_MouseButtonCallback);
  glfwSetScrollCallback(window, ImGui_ScrollCallback);
  glfwSetKeyCallback(window, ImGui_KeyCallback);
  glfwSetCharCallback(window, ImGui_CharCallback);

  return true;
}

void ImGui_NewFrame() {
  if (!g_FontTexture)
    ImGui_CreateDeviceObjects();

  ImGuiIO& io = ImGui::GetIO();

  // Setup display size (every frame to accommodate for window resizing)
  int w, h;
  int display_w, display_h;
  glfwGetWindowSize(window, &w, &h);
  glfwGetFramebufferSize(window, &display_w, &display_h);
  io.DisplaySize = ImVec2((float)w, (float)h);
  io.DisplayFramebufferScale = ImVec2((float)display_w / w, (float)display_h / h);

  // Setup time step
  double current_time = glfwGetTime();
  io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
  g_Time = current_time;

  // Setup inputs
  // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
  if (glfwGetWindowAttrib(window, GLFW_FOCUSED))
  {
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);   // Mouse position in screen coordinates (set to -1,-1 if no mouse / on another screen, etc.)
  } else
  {
    io.MousePos = ImVec2(-1, -1);
  }

  for (int i = 0; i < 3; i++)
  {
    io.MouseDown[i] = g_MousePressed[i] || glfwGetMouseButton(window, i) != 0;    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
    g_MousePressed[i] = false;
  }

  io.MouseWheel = g_MouseWheel;
  g_MouseWheel = 0.0f;

  // Hide OS mouse cursor if ImGui is drawing it
  glfwSetInputMode(window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

  // Start the frame
  ImGui::NewFrame();
}

float ROTOM::GRAPHICS::getTime() {
  return (float)glfwGetTime();
}

void ROTOM::GRAPHICS::windowInit(unsigned int width, unsigned int height) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(width, height, "ROTOM ENGINE", nullptr, nullptr);
  if (!window) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
  glewExperimental = GL_TRUE;

  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();

  //glViewport(0, 0, width, height);

  //glDepthRange(0, 1);
  //glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);
  glEnable(GL_BLEND);
  //glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  ImGui_Init(window, true);

  glClearColor(0.1f, 0.5f, 0.6f, 1.0f);
}

void ROTOM::GRAPHICS::windowDestroy() {
  ImGui_InvalidateDeviceObjects();
  ImGui::Shutdown();

  glfwDestroyWindow(window);
  glfwTerminate();
}

bool ROTOM::GRAPHICS::windowShouldClose() {
  return glfwWindowShouldClose(window) == 1;
}

void ROTOM::GRAPHICS::clearScreen() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ROTOM::GRAPHICS::clear() {
  clearScreen();
  g_MousePressed[0] = false;
  g_MousePressed[1] = false;
  g_MousePressed[2] = false;
  glfwPollEvents(); // Check and call events
  ImGui_NewFrame();
}

void ROTOM::GRAPHICS::swapBuffers() {
  //ImGui
  ImGui::Render();

  //SwapBuffers
  glfwSwapBuffers(window);
}

int ROTOM::GRAPHICS::screenWidth() {
  int width = 0, height = 0;
  glfwGetFramebufferSize(window, &width, &height);
  return width;
}

int ROTOM::GRAPHICS::screenHeight() {
  int width = 0, height = 0;
  glfwGetFramebufferSize(window, &width, &height);
  return height;
}

void ROTOM::GRAPHICS::setShader(ShaderData *shaderData, const char *vertexShaderSource, const char *fragmentShaderSource) {
  GLint success;
  GLchar infoLog[512];

  //Vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//Check for compile time errors
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    printf("ERROR: VertexShader\n%s\n", infoLog);
  }

  //Fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//Check for compile time errors
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    printf("ERROR: FragmentShader\n%s\n", infoLog);
  }
  
  //Link shaders
  shaderData->shaderProgram = glCreateProgram();
  glAttachShader(shaderData->shaderProgram, vertexShader);
  glAttachShader(shaderData->shaderProgram, fragmentShader);
  glLinkProgram(shaderData->shaderProgram);
  glGetProgramiv(shaderData->shaderProgram, GL_LINK_STATUS, &success);//Check for linking errors
  if (!success) {
    glGetProgramInfoLog(shaderData->shaderProgram, 512, nullptr, infoLog);
    printf("ERROR: ProgramShader\n%s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glUseProgram(shaderData->shaderProgram);

  //Get their uniform location
  shaderData->u_color = glGetUniformLocation(shaderData->shaderProgram, "u_color");
  shaderData->u_model = glGetUniformLocation(shaderData->shaderProgram, "u_model");
  shaderData->u_view = glGetUniformLocation(shaderData->shaderProgram, "u_view");
  shaderData->u_projection = glGetUniformLocation(shaderData->shaderProgram, "u_projection");
  shaderData->u_lightPosition = glGetUniformLocation(shaderData->shaderProgram, "u_lightPosition");
  shaderData->u_lightColor = glGetUniformLocation(shaderData->shaderProgram, "u_lightColor");
  shaderData->u_texture = glGetUniformLocation(shaderData->shaderProgram, "u_texture");
  shaderData->u_shininess = glGetUniformLocation(shaderData->shaderProgram, "u_shininess");
  shaderData->u_specularIntensity = glGetUniformLocation(shaderData->shaderProgram, "u_specularIntensity");
  shaderData->u_specularMaterial = glGetUniformLocation(shaderData->shaderProgram, "u_specularMaterial");
  shaderData->u_ambientStrength = glGetUniformLocation(shaderData->shaderProgram, "u_ambientStrength");
  shaderData->u_viewDirection = glGetUniformLocation(shaderData->shaderProgram, "u_viewDirection");
  shaderData->u_lightSpaceMatrix = glGetUniformLocation(shaderData->shaderProgram, "u_lightSpaceMatrix");
  shaderData->u_colorMap = glGetUniformLocation(shaderData->shaderProgram, "u_colorMap");
  shaderData->u_depthMap = glGetUniformLocation(shaderData->shaderProgram, "u_depthMap");
}

unsigned int ROTOM::GRAPHICS::setTexture(unsigned int *texture, unsigned char *image, int *textureWidth, int *textureHeight) {
  glGenTextures(1, texture);
  int textureActivePosition = GL_TEXTURE0 + ++textureID;
  glActiveTexture(textureActivePosition);
  glBindTexture(GL_TEXTURE_2D, *texture);
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *textureWidth, *textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  return textureActivePosition;
}

void ROTOM::GRAPHICS::releaseTexture(unsigned int *texture) {
  if (texture > 0) {
    glDeleteTextures(1, texture);
  }
}

void ROTOM::GRAPHICS::releaseMaterial(unsigned int *shaderProgram) {
  glDeleteProgram(*shaderProgram);
}

ROTOM::ShaderData *shaderData;
ROTOM::MaterialSettings* materialSettings;
ROTOM::Light *light = nullptr;
glm::fvec3 lightPosition;
float *lightColor = nullptr, *specularIntensity = nullptr, *specularMaterial = nullptr, *color = nullptr;
void ROTOM::GRAPHICS::drawObject(CommandDrawObjectData *commandDrawObjectData, std::vector<std::shared_ptr<Light>> *lights, float *projectionMatrix, float *viewMatrix) {
  shaderData = &commandDrawObjectData->shaderData;
  materialSettings = &commandDrawObjectData->materialSettings;
  specularMaterial = commandDrawObjectData->materialData.specularMaterial;
  color = materialSettings->color_;

  glUseProgram(shaderData->shaderProgram);

  //Textures
  glBindTexture(GL_TEXTURE_2D, actualRenderTarget.framebufferData_.textureColor); //Texture ColorBuffer
  glBindTexture(GL_TEXTURE_2D, actualRenderTarget.framebufferData_.textureDepth); //Texture DepthBuffer
  glBindTexture(GL_TEXTURE_2D, commandDrawObjectData->material_texture); //Texture Object

  //Node
  glUniformMatrix4fv(shaderData->u_model, 1, GL_FALSE, commandDrawObjectData->drawable_worldMatrix);
  glUniformMatrix4fv(shaderData->u_view, 1, GL_FALSE, viewMatrix);
  glUniformMatrix4fv(shaderData->u_projection, 1, GL_FALSE, projectionMatrix);
  glUniform3f(shaderData->u_viewDirection, -viewMatrix[12], -viewMatrix[13], -viewMatrix[14]);
  //printf("%f %f %f %f\n", viewMatrix[0], viewMatrix[1], viewMatrix[2], viewMatrix[3]);
  //printf("%f %f %f %f\n", viewMatrix[4], viewMatrix[5], viewMatrix[6], viewMatrix[7]);
  //printf("%f %f %f %f\n", viewMatrix[8], viewMatrix[9], viewMatrix[10], viewMatrix[11]);
  //printf("%f %f %f %f\n\n", viewMatrix[12], viewMatrix[13], viewMatrix[14], viewMatrix[15]);

  //Material
  glUniform1f(shaderData->u_shininess, commandDrawObjectData->materialData.shininess);
  glUniform3f(shaderData->u_specularMaterial, specularMaterial[0], specularMaterial[1], specularMaterial[2]);
  glUniform1f(shaderData->u_ambientStrength, commandDrawObjectData->materialData.ambientStrength);
  
  //Material Settings
  glUniform4f(shaderData->u_color, color[0], color[1], color[2], color[3]);

  //Light
  for (unsigned int i = 0; i < lights->size(); ++i) {
    light = lights->at(i).get();
    lightPosition = light->position();
    lightColor = light->materialSettings()->color_;
    specularIntensity = light->specularIntensity_;
    glUniformMatrix4fv(shaderData->u_lightSpaceMatrix, 1, GL_FALSE, light->spaceMatrix());
    glUniform3f(shaderData->u_lightPosition, lightPosition.x, lightPosition.y, lightPosition.z);
    glUniform3f(shaderData->u_lightColor, lightColor[0], lightColor[1], lightColor[2]);
    glUniform3f(shaderData->u_specularIntensity, specularIntensity[0], specularIntensity[1], specularIntensity[2]);
  }

  glBindVertexArray(commandDrawObjectData->geometry_VAO);
  glDrawElements(GL_TRIANGLES, commandDrawObjectData->geometry_veterCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void ROTOM::GRAPHICS::loadGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int numberOfElementsPerVertex, unsigned int vertexCount, float *vertex, int *index) {
  //Release the elements in case the user load a geometry inside a geometry
  releaseGeometry(VAO, VBO, EBO);

  glGenVertexArrays(1, VAO);
  glGenBuffers(1, VBO);
  glGenBuffers(1, EBO);

  glBindVertexArray(*VAO); // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  
  //Vertex
  glBindBuffer(GL_ARRAY_BUFFER, *VBO); //Bind the buffer to the GL_ARRAY_BUFFER target
  glBufferData(GL_ARRAY_BUFFER, numberOfElementsPerVertex * vertexCount, vertex, GL_STATIC_DRAW); //Copies the previously defined vertex data into the buffer's memory

  //Index
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertexCount, index, GL_STATIC_DRAW);

  //Position attribute
  int numberOfPositions = 3;
  glVertexAttribPointer(0, numberOfPositions, GL_FLOAT, GL_FALSE, numberOfElementsPerVertex, (GLvoid*)0);
  glEnableVertexAttribArray(0);

  //Normal attribute
  int numberOfNormals = 3;
  glVertexAttribPointer(1, numberOfNormals, GL_FLOAT, GL_FALSE, numberOfElementsPerVertex, (GLvoid*)(numberOfPositions * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  //UV attribute
  int numberOfUVs = 2;
  glVertexAttribPointer(2, numberOfUVs, GL_FLOAT, GL_FALSE, numberOfElementsPerVertex, (GLvoid*)((numberOfPositions + numberOfNormals) * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void ROTOM::GRAPHICS::releaseGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO) {
  if (VAO > 0) {
    glDeleteVertexArrays(1, VAO);
  }
  if (EBO > 0) {
    glDeleteBuffers(1, EBO);
  }
  if (VBO > 0) {
    glDeleteBuffers(1, VBO);
  }
}

void ROTOM::GRAPHICS::genRenderBuffer(int *colorActivePosition, int *depthActivePosition, unsigned int *colorBuffer, unsigned int *depthBuffer, unsigned int *framebuffer, unsigned int width, unsigned int height) {
  //Framebuffer
  glGenFramebuffers(1, framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, *framebuffer);

  //Color texture
  glGenTextures(1, colorBuffer);
  *colorActivePosition = GL_TEXTURE0 + ++textureID;
  glActiveTexture(*colorActivePosition);
  glBindTexture(GL_TEXTURE_2D, *colorBuffer);
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *colorBuffer, 0);

  //Depth texture
  glGenTextures(1, depthBuffer);
  *depthActivePosition = GL_TEXTURE0 + ++textureID;
  glActiveTexture(*depthActivePosition);
  glBindTexture(GL_TEXTURE_2D, *depthBuffer);
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthBuffer, 0);

  //Check status
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    system("pause");
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ROTOM::GRAPHICS::beginFramebuffer(RenderTarget *renderTarget) {
  glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->framebufferData_.framebuffer);
  actualRenderTarget = *renderTarget;
  clearScreen();
}

void ROTOM::GRAPHICS::endFramebuffer() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}