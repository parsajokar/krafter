#include "glm/gtc/matrix_transform.hpp"

#include "window.h"
#include "game.h"
#include "camera.h"

namespace Krafter
{

Camera::Camera(const glm::vec3& position, float fov)
    : speed(10.0f), sensitivity(5.0f),
    _isControlled(true), _isSpaceReleased(true),
    _position(position), _fov(fov),
    _pitch(0.0f), _yaw(0.0f), _lastCursorPosition(Window::Get()->GetCursorPosition())
{
    UpdateProjection();
}

void Camera::Update()
{
    if (Window::Get()->IsKeyDown(Key::SPACE) && _isSpaceReleased)
    {
        ToggleState();
        _isSpaceReleased = false;
    }
    if (!Window::Get()->IsKeyDown(Key::SPACE))
    {
        _isSpaceReleased = true;
    }

    if (_isControlled)
    {
        float delta = Game::Get()->GetDelta();

        glm::vec2 cursorPosition = Window::Get()->GetCursorPosition();
        glm::vec2 cursorOffset = cursorPosition - _lastCursorPosition;
        _lastCursorPosition = cursorPosition;

        _pitch -= cursorOffset.y * sensitivity * delta;
        _yaw += cursorOffset.x * sensitivity * delta;

        _pitch = glm::clamp(_pitch, glm::radians(-89.99f), glm::radians(89.99f));

        glm::vec3 direction = glm::normalize(glm::vec3(
            glm::cos(_yaw) * glm::cos(_pitch),
            glm::sin(_pitch),
            glm::sin(_yaw) * glm::cos(_pitch)
        ));
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(direction, up));

        if (Window::Get()->IsKeyDown(Key::W))
        {
            _position += direction * speed * delta;
        }
        if (Window::Get()->IsKeyDown(Key::S))
        {
            _position -= direction * speed * delta;
        }
        if (Window::Get()->IsKeyDown(Key::D))
        {
            _position += right * speed * delta;
        }
        if (Window::Get()->IsKeyDown(Key::A))
        {
            _position -= right * speed * delta;
        }

        glm::mat4 transform = glm::lookAt(_position, _position + direction, up);
        _viewProjection = _projection * transform;
    }
}

void Camera::UpdateProjection()
{
    const glm::uvec2& size = Window::Get()->GetSize();
    if (size.x > 0 && size.y > 0)
    {
        float aspectRatio = (float)size.x / (float)size.y;
        _projection = glm::perspective(_fov, aspectRatio, 0.1f, 1000.0f);
    }
}

void Camera::ToggleState()
{
    if (_isControlled)
    {
        Window::Get()->EnableCursor(true);
    }
    else
    {
        Window::Get()->EnableCursor(false);
        _lastCursorPosition = Window::Get()->GetCursorPosition();
    }

    _isControlled = !_isControlled;
}

} // namespace Krafter
