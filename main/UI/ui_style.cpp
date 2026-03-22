#include "ui_style.h"
#include "../../imgui-master/imgui.h"

void ApplyStyle() {
  ImGuiStyle &style = ImGui::GetStyle();

  style.WindowRounding = 8.0f;
  style.FrameRounding = 6.0f;
  style.ScrollbarRounding = 4.0f;

  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
  style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.8f, 1.0f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.5f, 0.9f, 1.0f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.3f, 0.7f, 1.0f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
  style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}
