#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec2 Position;
    float Zoom;

    Camera(glm::vec2 position = glm::vec2(0.0f, 0.0f));

    // Get the view matrix, which translates the world in the opposite direction of the camera
    glm::mat4 GetViewMatrix() const;
    
    // Update the camera position to center on a target (e.g., the player)
    void Follow(glm::vec2 targetPosition, float screenWidth, float screenHeight);
};
