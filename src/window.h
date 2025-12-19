#pragma once

#include "glm/glm.hpp"

typedef struct GLFWwindow GLFWwindow;
using WindowId = GLFWwindow*;

namespace Krafter
{

class Window
{
public:
    static void Init();
    static void Deinit();
    inline static Window* Get() { return _instance; }

    bool IsOpen() const;
    void PollEvents() const;
    void SwapBuffers() const;

    inline WindowId GetId() const { return _id; }
    inline const glm::uvec2& GetSize() const { return _size; }

private:
    inline static Window* _instance;

    Window();
    ~Window();

    WindowId _id;
    glm::uvec2 _size;

    friend void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};

} // namespace Krafter