#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer {
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();
    
    void DrawSprite(unsigned int texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 texOffset = glm::vec2(0.0f), glm::vec2 texScale = glm::vec2(1.0f));

private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};
