#pragma once

#include <cstdint>

namespace Krafter
{

class Renderer
{
public:
    static void Init();
    static void Deinit();
    inline static Renderer* Get() { return _instance; }

    void ClearBuffers() const;
    void DrawRectangle(float r, float g, float b, float a) const;

private:
    inline static Renderer* _instance;

    Renderer();
    ~Renderer();

    uint32_t _program;
    int32_t _programColorLocation;

    uint32_t _vertexArray;
    uint32_t _vertexBuffer;
    uint32_t _elementBuffer;
};

} // namespace Krafter
