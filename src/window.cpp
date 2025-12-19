#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "renderer.h"
#include "window.h"

namespace Krafter
{

void Window::Init()
{
    _instance = new Window();
}

void Window::Deinit()
{
    delete _instance;
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(_id);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(_id);
}

float Window::GetTime() const
{
    return glfwGetTime();
}

bool Window::IsKeyDown(Key key) const
{
    return glfwGetKey(_id, (int)key) == GLFW_PRESS;
}

void Window::EnableCursor(bool state) const
{
    glfwSetInputMode(_id, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

glm::vec2 Window::GetCursorPosition() const
{
    double x;
    double y;
    glfwGetCursorPos(_id, &x, &y);
    return glm::vec2(x, y);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Window* win = Window::Get();
    win->_size.x = width;
    win->_size.y = height;

    glViewport(0, 0, win->GetSize().x, win->GetSize().y);

    Renderer::Get()->GetCamera().UpdateProjection();
}

Window::Window()
    : _size(1280, 720)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _id = glfwCreateWindow(_size.x, _size.y, "Krafter", nullptr, nullptr);
    glfwMakeContextCurrent(_id);

    glfwSetFramebufferSizeCallback(_id, FramebufferSizeCallback);

    EnableCursor(false);
}

Window::~Window()
{
    glfwDestroyWindow(_id);
    glfwTerminate();
}

} // namespace Krafter