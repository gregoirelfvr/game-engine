#include <vector>
#define GL_SILENCE_DEPRECATION
#include "../imgui-master/backends/imgui_impl_glfw.h"
#include "../imgui-master/backends/imgui_impl_opengl3.h"
#include "../imgui-master/imgui.h"
#include <GLFW/glfw3.h>

class Character;

int character_widget(Character &player);
int menu(std::vector<Character> &player_team);