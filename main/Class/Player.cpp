#include "Player.h"
#include "Character.h"
#include "../Engine/SpriteRenderer.h"

Player::Player(glm::vec2 pos, glm::vec2 size, unsigned int sprite, std::vector<Character> party) 
    : Position(pos), Size(size), Sprite(sprite), Party(party) {
    FacingDirection = Direction::DOWN;
    IsMoving = false;
    AnimationTimer = 0.0f;
    CurrentFrame = 0;
}

void Player::Update(float deltaTime) {
    if (IsMoving) {
        AnimationTimer += deltaTime;
        if (AnimationTimer >= 0.15f) { // 0.15 seconds per frame
            AnimationTimer = 0.0f;
            CurrentFrame = (CurrentFrame + 1) % 4; // 4 frames per animation
        }
    } else {
        CurrentFrame = 0; // Idle frame
        AnimationTimer = 0.0f;
    }
}

void Player::Draw(SpriteRenderer &renderer) {
    // The sprite sheet is 4 rows by 4 columns.
    glm::vec2 texScale = glm::vec2(1.0f / 4.0f, 1.0f / 4.0f);
    
    // row corresponds to direction, col corresponds to animation frame
    float row = (float)static_cast<int>(FacingDirection);
    float col = (float)CurrentFrame;

    glm::vec2 texOffset = glm::vec2(col * texScale.x, row * texScale.y);

    renderer.DrawSprite(this->Sprite, this->Position, this->Size, 0.0f, glm::vec3(1.0f), texOffset, texScale);
}
