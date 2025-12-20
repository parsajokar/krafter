#include <string>
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "stb_image.h"

#include "renderer.h"

namespace Krafter
{

Texture2D::Texture2D(std::string_view path)
{
    stbi_set_flip_vertically_on_load(true);

    int32_t channels_in_file;
    uint8_t* data = stbi_load(path.data(), &_size.x, &_size.y, &channels_in_file, 0);
    if (!data)
    {
        std::cerr << "ERROR!\n";
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &_id);

    glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureStorage2D(_id, 1, GL_RGBA8, _size.x, _size.y);
    glTextureSubImage2D(_id, 0, 0, 0, _size.x, _size.y, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_id);
}

void Texture2D::Bind(uint32_t unit) const
{
    glBindTextureUnit(unit, _id);
}

ShaderProgram::ShaderProgram(std::string_view vertexShaderSource, std::string_view fragmentShaderSource)
{
    _id = glCreateProgram();
    uint32_t vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource.data());
    uint32_t fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource.data());

    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);

    glLinkProgram(_id);
    glValidateProgram(_id);

    glDetachShader(_id, vertexShader);
    glDetachShader(_id, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_id);
}

void ShaderProgram::Bind() const
{
    glUseProgram(_id);
}

void ShaderProgram::SetUniformInt(int32_t location, int32_t value) const
{
    glUniform1i(location, value);
}

void ShaderProgram::SetUniformVec4(int32_t location, const glm::vec4& value) const
{
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniformMat4(int32_t location, const glm::mat4& value) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

uint32_t ShaderProgram::CreateShader(uint32_t type, const char* source)
{
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    return shader;
}

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

void Renderer::DrawRectangle(const glm::vec4& color) const
{
    _program->Bind();
    _program->SetUniformMat4(0, _camera.GetViewProjection());
    _program->SetUniformVec4(1, color);
    _texture->Bind(0);
    _program->SetUniformInt(2, 0);
    glBindVertexArray(_vertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

static std::string vertexShaderSource =
R"(
#version 450 core

layout(location = 0) uniform mat4 u_ViewProjection;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UvCoords;

out vec2 v_UvCoords;

void main()
{
    v_UvCoords = a_UvCoords;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
)";

static std::string fragmentShaderSource =
R"(
#version 450 core

layout(location = 1) uniform vec4 u_Color;
layout(location = 2) uniform sampler2D u_Texture;

layout(location = 0) out vec4 o_Color;

in vec2 v_UvCoords;

void main()
{
    o_Color = u_Color * texture(u_Texture, v_UvCoords);
}
)";

Renderer::Renderer()
    : _camera(glm::vec3(0.0f), glm::radians(80.0f))
{
    gladLoadGL(glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    _program = std::make_shared<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
    _texture = std::make_shared<Texture2D>("assets/texture.png");

    glCreateVertexArrays(1, &_vertexArray);
    glCreateBuffers(1, &_vertexBuffer);
    glCreateBuffers(1, &_elementBuffer);

    float vertexBufferData[] =
    {
        0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, -1.0f, 0.0f, 1.0f
    };

    uint32_t elementBufferData[] = { 0, 2, 1, 0, 2, 3 };

    glNamedBufferData(_vertexBuffer, 4 * 5 * sizeof(float), vertexBufferData, GL_STATIC_DRAW);
    glNamedBufferData(_elementBuffer, 6 * sizeof(uint32_t), elementBufferData, GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(_vertexArray, 0, _vertexBuffer, 0, 5 * sizeof(float));
    glVertexArrayElementBuffer(_vertexArray, _elementBuffer);

    glEnableVertexArrayAttrib(_vertexArray, 0);
    glVertexArrayAttribBinding(_vertexArray, 0, 0);
    glVertexArrayAttribFormat(_vertexArray, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(_vertexArray, 1);
    glVertexArrayAttribBinding(_vertexArray, 1, 0);
    glVertexArrayAttribFormat(_vertexArray, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &_elementBuffer);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteVertexArrays(1, &_vertexArray);
}

} // namespace Krafter
