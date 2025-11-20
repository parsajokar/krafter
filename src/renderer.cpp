#include <string>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "renderer.h"

namespace Krafter
{

void Renderer::Init()
{
    _instance = new Renderer();
}

void Renderer::Deinit()
{
    delete _instance;
}

void Renderer::ClearBuffers() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawRectangle(float r, float g, float b, float a) const
{
    glUseProgram(_program);
    glUniform4f(_programColorLocation, r, g, b, a);
    glBindVertexArray(_vertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

static uint32_t CreateShader(uint32_t type, const char* source)
{
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    return shader;
}

static std::string vertexShaderSource =
R"(
#version 450 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Color;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
}
)";

static std::string fragmentShaderSource =
R"(
#version 450 core

layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;

void main()
{
    o_Color = u_Color;
}
)";

Renderer::Renderer()
{
    gladLoadGL(glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1, 0.1, 0.1, 1.0);

    _program = glCreateProgram();
    uint32_t vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    uint32_t fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    glLinkProgram(_program);
    glValidateProgram(_program);

    glDetachShader(_program, vertexShader);
    glDetachShader(_program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    _programColorLocation = glGetUniformLocation(_program, "u_Color");

    glCreateVertexArrays(1, &_vertexArray);
    glCreateBuffers(1, &_vertexBuffer);
    glCreateBuffers(1, &_elementBuffer);

    float vertexBufferData[] =
    {
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0
    };

    uint32_t elementBufferData[] = { 0, 2, 1, 0, 2, 3 };

    glNamedBufferData(_vertexBuffer, 4 * 3 * sizeof(float), vertexBufferData, GL_STATIC_DRAW);
    glNamedBufferData(_elementBuffer, 6 * sizeof(uint32_t), elementBufferData, GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(_vertexArray, 0, _vertexBuffer, 0, 3 * sizeof(float));
    glVertexArrayElementBuffer(_vertexArray, _elementBuffer);

    glEnableVertexArrayAttrib(_vertexArray, 0);
    glVertexArrayAttribBinding(_vertexArray, 0, 0);
    glVertexArrayAttribFormat(_vertexArray, 0, 3, GL_FLOAT, GL_FALSE, 0);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &_elementBuffer);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteVertexArrays(1, &_vertexArray);

    glDeleteProgram(_program);
}

} // namespace Krafter