#pragma once

#include <glm/glm.hpp>
#include <vector>

// Forward declarations
class Character;
class SpriteRenderer;

enum class Direction {
    DOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3
};

class Player {
public:
    glm::vec2 Position;
    glm::vec2 Size;
    unsigned int Sprite;
    std::vector<Character> Party;

    Direction FacingDirection;
    bool IsMoving;
    float AnimationTimer;
    int CurrentFrame;

    Player(glm::vec2 pos, glm::vec2 size, unsigned int sprite, std::vector<Character> party);
    void Update(float deltaTime);
    void Draw(SpriteRenderer &renderer);
};
