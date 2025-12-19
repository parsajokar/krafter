#pragma once

#include "glm/glm.hpp"

namespace Krafter
{

class Camera
{
public:
    Camera(const glm::vec3& position, float fov);

    void Update();
    void UpdateProjection();
    inline const glm::mat4& GetViewProjection() const { return _viewProjection; }

    float speed;
    float sensitivity;

private:
    void ToggleState();

    bool _isControlled;
    bool _isSpaceReleased;

    glm::vec3 _position;
    float _fov;

    float _pitch;
    float _yaw;
    glm::vec2 _lastCursorPosition;

    glm::mat4 _projection;
    glm::mat4 _viewProjection;
};

} // namespace Krafter
