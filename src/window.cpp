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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Window* win = Window::Get();
    win->_size.x = width;
    win->_size.y = height;

    glViewport(0, 0, win->GetSize().x, win->GetSize().y);

    Camera& cam = Renderer::Get()->GetCamera();
    cam.UpdateProjection();
    cam.UpdateViewProjection();
}

Window::Window()
{
    _size = glm::uvec2(1280, 720);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _id = glfwCreateWindow(_size.x, _size.y, "Krafter", nullptr, nullptr);
    glfwMakeContextCurrent(_id);

    glfwSetFramebufferSizeCallback(_id, FramebufferSizeCallback);
}

Window::~Window()
{
    glfwDestroyWindow(_id);
    glfwTerminate();
}

} // namespace Krafter