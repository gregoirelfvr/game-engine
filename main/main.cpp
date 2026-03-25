#include "Class/Player.h"
#include "Class/Character.h"
#include "Engine/Shader.h"
#include "Engine/SpriteRenderer.h"
#include "Engine/Camera.h"
#include "UI/menu.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

bool showMenu = false;
bool iKeyPressed = false;

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (key == GLFW_KEY_I) {
    if (action == GLFW_PRESS) {
      if (!iKeyPressed) {
        showMenu = !showMenu;
        iKeyPressed = true;
      }
    } else if (action == GLFW_RELEASE) {
      iKeyPressed = false;
    }
  }
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(1280, 720, "GOA X", NULL, NULL);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  InitUI(window);

  Character char1("Greg", "Human", 100, 1,
                  "../assets/characters/temp_gold.png");
  Character char2("AntonioDeLaPizzeria", "Human", 100, 1,
                  "../assets/characters/temp_red.png");
  std::vector<Character> playerTeam = {char1, char2};

  const char *vShaderCode = R"(
      #version 330 core
      layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
      out vec2 TexCoords;
      uniform mat4 model;
      uniform mat4 view;
      uniform mat4 projection;
      uniform vec2 texOffset;
      uniform vec2 texScale;
      void main() {
          TexCoords = vertex.zw * texScale + texOffset;
          gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
      }
  )";
  const char *fShaderCode = R"(
      #version 330 core
      in vec2 TexCoords;
      out vec4 color;
      uniform sampler2D image;
      uniform vec3 spriteColor;
      void main() {    
          color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
          if (color.a < 0.1) discard;
      }
  )";

  Shader spriteShader;
  spriteShader.Compile(vShaderCode, fShaderCode);

  glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
  spriteShader.Use();
  spriteShader.SetInteger("image", 0);
  spriteShader.SetMatrix4("projection", projection);

  SpriteRenderer *renderer = new SpriteRenderer(spriteShader);

  GLuint playerTexture = 0;
  int w, h;
  LoadTextureFromFile("../assets/characters/temp_player.png", &playerTexture,
                      &w, &h);

  Player mainPlayer(glm::vec2(640.0f, 360.0f), glm::vec2(64.0f, 64.0f),
                    playerTexture, playerTeam);

  Camera camera;

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwPollEvents();

    if (!showMenu) {
      float velocity = 300.0f * deltaTime;
      mainPlayer.IsMoving = false;

      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mainPlayer.Position.y -= velocity;
        mainPlayer.FacingDirection = Direction::UP;
        mainPlayer.IsMoving = true;
      } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mainPlayer.Position.y += velocity;
        mainPlayer.FacingDirection = Direction::DOWN;
        mainPlayer.IsMoving = true;
      } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mainPlayer.Position.x -= velocity;
        mainPlayer.FacingDirection = Direction::LEFT;
        mainPlayer.IsMoving = true;
      } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mainPlayer.Position.x += velocity;
        mainPlayer.FacingDirection = Direction::RIGHT;
        mainPlayer.IsMoving = true;
      }

      mainPlayer.Update(deltaTime);
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    camera.Follow(mainPlayer.Position, 1280.0f, 720.0f);
    spriteShader.Use();
    spriteShader.SetMatrix4("view", camera.GetViewMatrix());

    mainPlayer.Draw(*renderer);

    if (showMenu) {
      RenderUI(mainPlayer.Party);
    }

    glfwSwapBuffers(window);
  }

  CleanupUI();
  delete renderer;
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
