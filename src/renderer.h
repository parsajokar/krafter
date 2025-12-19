#pragma once

#include <cstdint>

#include "camera.h"

namespace Krafter
{

class Renderer
{
public:
    static void Init();
    static void Deinit();
    inline static Renderer* Get() { return _instance; }

    inline Camera& GetCamera() { return _camera; }

    void ClearBuffers() const;
    void DrawRectangle(float r, float g, float b, float a) const;

private:
    inline static Renderer* _instance;

    Renderer();
    ~Renderer();

    Camera _camera;

    uint32_t _program;

    uint32_t _vertexArray;
    uint32_t _vertexBuffer;
    uint32_t _elementBuffer;
};

} // namespace Krafter
