#pragma once
#include <vector>
#define GL_SILENCE_DEPRECATION
#include "../imgui-master/backends/imgui_impl_glfw.h"
#include "../imgui-master/backends/imgui_impl_opengl3.h"
#include "../imgui-master/imgui.h"
#include <GLFW/glfw3.h>

class Character;

int CharacterWidget(Character &player);
void InitUI(GLFWwindow* window);
void RenderUI(std::vector<Character> &player_team);
void CleanupUI();
bool LoadTextureFromFile(const char *filename, GLuint *out_texture, int *out_width, int *out_height);