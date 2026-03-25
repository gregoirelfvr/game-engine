#include "Camera.h"

Camera::Camera(glm::vec2 position) : Position(position), Zoom(1.0f) {}

glm::mat4 Camera::GetViewMatrix() const {
    glm::mat4 view = glm::mat4(1.0f);
    // The camera moves the world in the opposite direction
    view = glm::translate(view, glm::vec3(-Position.x, -Position.y, 0.0f));
    return view;
}

void Camera::Follow(glm::vec2 targetPosition, float screenWidth, float screenHeight) {
    // Center the camera on the target
    Position.x = targetPosition.x - (screenWidth / 2.0f);
    Position.y = targetPosition.y - (screenHeight / 2.0f);
}
