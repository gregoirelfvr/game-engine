#include "menu.h"
#include "../Class/character_class.cpp"
#include "../libs/stb_image.h"
#include "ui_style.h"
#include <map>

bool LoadTextureFromFile(const char *filename, GLuint *out_texture,
                         int *out_width, int *out_height) {
  int image_width = 0;
  int image_height = 0;
  unsigned char *image_data =
      stbi_load(filename, &image_width, &image_height, NULL, 4);
  if (image_data == NULL)
    return false;

  GLuint image_texture;
  glGenTextures(1, &image_texture);
  glBindTexture(GL_TEXTURE_2D, image_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image_data);
  stbi_image_free(image_data);

  *out_texture = image_texture;
  *out_width = image_width;
  *out_height = image_height;

  return true;
}

int menu(std::vector<Character> &player_team) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for Mac
#endif

  GLFWwindow *window = glfwCreateWindow(1280, 720, "GOA X", NULL, NULL);
  glfwMakeContextCurrent(window);

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  ApplyStyle();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (Character &player : player_team) {
      character_widget(player);
    }

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

int character_widget(Character &player) {
  ImGui::Begin("Character Stats");

  static std::map<std::string, GLuint> texture_cache;
  std::string icon_path = player.getIcon();

  if (!icon_path.empty()) {
    if (texture_cache.find(icon_path) == texture_cache.end()) {
      GLuint my_image_texture = 0;
      int my_image_width = 0;
      int my_image_height = 0;
      bool ret = LoadTextureFromFile(icon_path.c_str(), &my_image_texture,
                                     &my_image_width, &my_image_height);
      if (ret) {
        texture_cache[icon_path] = my_image_texture;
      } else {
        texture_cache[icon_path] = 0;
        fprintf(stderr, "Failed to load image: %s\n", icon_path.c_str());
      }
    }

    GLuint tex_id = texture_cache[icon_path];
    if (tex_id != 0) {
      ImGui::Image((ImTextureID)(intptr_t)tex_id, ImVec2(75, 75));
      ImGui::SameLine();
    }
  }

  ImGui::BeginGroup();
  ImGui::Text("Name: %s | Level: %d | Type: %s", player.getName().c_str(),
              player.getLevel(), player.getType().c_str());

  ImGui::Separator();

  float hp_fraction = (float)player.getHp() / (float)player.getMaxHp();
  char hp_overlay[32];
  snprintf(hp_overlay, sizeof(hp_overlay), "HP: %d / %d", player.getHp(),
           player.getMaxHp());

  // Color coding for health bar
  ImVec4 hp_color;
  if (hp_fraction > 0.5f) {
    hp_color = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
  } else if (hp_fraction > 0.2f) {
    hp_color = ImVec4(0.8f, 0.8f, 0.2f, 1.0f);
  } else {
    hp_color = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
  }

  ImGui::PushStyleColor(ImGuiCol_PlotHistogram, hp_color);
  ImGui::ProgressBar(hp_fraction, ImVec2(-FLT_MIN, 0.0f), hp_overlay);
  ImGui::PopStyleColor();
  ImGui::EndGroup();

  ImGui::End();
  return 0;
}
