#include "menu.h"
#include "../character_class.cpp"

int menu(Character &player) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for Mac
#endif

  GLFWwindow *window = glfwCreateWindow(800, 600, "Minimal Text", NULL, NULL);
  glfwMakeContextCurrent(window);

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::Begin("Dialogue Box");
    // ImGui::Image(ImGui::GetIO().Fonts->TexID, ImVec2(100, 100));
    // ImGui::Text("A wild Pikachu appeared!");
    // ImGui::Text("What will you do?");
    // ImGui::End();

    character_widget(player);

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

  ImGui::End();
  return 0;
}