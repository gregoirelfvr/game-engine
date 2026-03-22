#define GL_SILENCE_DEPRECATION
#include "../../imgui-master/backends/imgui_impl_glfw.h"
#include "../../imgui-master/backends/imgui_impl_opengl3.h"
#include "../../imgui-master/imgui.h"
#include <GLFW/glfw3.h>

int menu() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for Mac
#endif

  GLFWwindow *window = glfwCreateWindow(800, 600, "Minimal Text", NULL, NULL);
  glfwMakeContextCurrent(window);

  // 2. Init ImGui
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  // 3. The Game Loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // Start a new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // --- DRAW YOUR TEXT HERE ---
    ImGui::Begin("Dialogue Box");
    ImGui::Text("A wild Pikachu appeared!");
    ImGui::Text("What will you do?");
    ImGui::End();
    // ---------------------------

    // Render everything
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT); // Clears the background to default black
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  // 4. Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}