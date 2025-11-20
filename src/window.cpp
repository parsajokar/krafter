#include "GLFW/glfw3.h"
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

Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _id = glfwCreateWindow(1280, 720, "Krafter", nullptr, nullptr);
    glfwMakeContextCurrent(_id);

    glfwSetFramebufferSizeCallback(
        _id,
        [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    );
}

Window::~Window()
{
    glfwDestroyWindow(_id);
    glfwTerminate();
}

} // namespace Krafter