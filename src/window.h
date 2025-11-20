#pragma once

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

private:
    inline static Window* _instance;

    Window();
    ~Window();

    WindowId _id;
};

} // namespace Krafter