#pragma once

#include "glm/glm.hpp"

namespace Krafter
{

class Camera
{
public:
    Camera(const glm::vec3& position, float fov);

    inline const glm::vec3& GetPosition() const { return _position; }
    void SetPosition(const glm::vec3& position);

    inline const glm::mat4& GetViewProjection() const { return _viewProjection; }

    void UpdateTransform();
    void UpdateProjection();
    void UpdateViewProjection();

private:
    glm::vec3 _position;
    float _fov;

    glm::mat4 _transform;
    glm::mat4 _projection;
    glm::mat4 _viewProjection;
};

} // namespace Krafter
