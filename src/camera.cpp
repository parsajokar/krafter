#include "glm/gtc/matrix_transform.hpp"

#include "window.h"
#include "camera.h"

namespace Krafter
{

Camera::Camera(const glm::vec3& position, float fov)
    : _position(position), _fov(fov)
{
    UpdateTransform();
    UpdateProjection();
    UpdateViewProjection();
}

void Camera::SetPosition(const glm::vec3& position)
{
    _position = position;
    UpdateTransform();
    UpdateViewProjection();
}

void Camera::UpdateTransform()
{
    _transform = glm::translate(glm::mat4(1.0f), _position);
}

void Camera::UpdateProjection()
{
    const glm::uvec2& size = Window::Get()->GetSize();
    float aspectRatio = (float)size.x / (float)size.y;
    _projection = glm::perspective(_fov, aspectRatio, 0.1f, 1000.0f);
}

void Camera::UpdateViewProjection()
{
    _viewProjection = _projection * _transform;
}

} // namespace Krafter
