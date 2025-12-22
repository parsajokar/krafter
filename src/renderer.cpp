#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
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
        std::cerr << "[FILE] Could not read " << path << std::endl;
        assert(false);
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

ShaderProgram::ShaderProgram(std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
{
    std::string vertexShaderSource = std::move(ReadFileAsString(vertexShaderPath));
    std::string fragmentShaderSource = std::move(ReadFileAsString(fragmentShaderPath));

    _id = glCreateProgram();
    uint32_t vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
    uint32_t fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

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

std::string ShaderProgram::ReadFileAsString(std::string_view path)
{
    std::ifstream file = std::ifstream(path.data(), std::ios::binary);
    if (!file)
    {
        std::cerr << "[FILE] Could not read " << path << std::endl;
        assert(false);
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();

    std::string result = std::string(size, '\0');
    file.seekg(0, std::ios::beg);
    file.read(result.data(), size);

    return result;
}

uint32_t ShaderProgram::CreateShader(uint32_t type, const char* source)
{
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    return shader;
}

ChunkMesh::ChunkMesh(const Chunk& chunk)
{
    const glm::vec2 pos = chunk.GetPosition();

    std::vector<float> vertexBufferData;
    std::vector<uint32_t> elementBufferData;

    // constexpr int32_t dx[] = { -1, 1, 0, 0, 0, 0 };
    // constexpr int32_t dy[] = { 0, 0, -1, 1, 0, 0 };
    // constexpr int32_t dz[] = { 0, 0, 0, 0, -1, 1 };

    uint32_t offset = 0;
    for (int32_t x = 0; x < Chunk::WIDTH; x++)
    {
        for (int32_t y = 0; y < Chunk::HEIGHT; y++)
        {
            for (int32_t z = 0; z < Chunk::WIDTH; z++)
            {
                /*
                for (size_t k = 0; k < 6; k++)
                {
                    int32_t nx = x + dx[k];
                    int32_t ny = y + dy[k];
                    int32_t nz = z + dz[k];

                    if (chunk.GetBlock(glm::ivec3(nx, ny, nz)) == Block::AIR)
                    {

                    }
                }
                */

                vertexBufferData.push_back(pos.x + x);
                vertexBufferData.push_back(y);
                vertexBufferData.push_back(pos.y + z);
                vertexBufferData.push_back(0.0f);
                vertexBufferData.push_back(0.0f);

                vertexBufferData.push_back(pos.x + x + 1.0f);
                vertexBufferData.push_back(y);
                vertexBufferData.push_back(pos.y + z);
                vertexBufferData.push_back(1.0f);
                vertexBufferData.push_back(0.0f);

                vertexBufferData.push_back(pos.x + x + 1.0f);
                vertexBufferData.push_back(y);
                vertexBufferData.push_back(pos.y + z + 1.0f);
                vertexBufferData.push_back(1.0f);
                vertexBufferData.push_back(1.0f);

                vertexBufferData.push_back(pos.x + x);
                vertexBufferData.push_back(y);
                vertexBufferData.push_back(pos.y + z + 1.0f);
                vertexBufferData.push_back(0.0f);
                vertexBufferData.push_back(1.0f);

                elementBufferData.push_back(offset);
                elementBufferData.push_back(offset + 2);
                elementBufferData.push_back(offset + 1);

                elementBufferData.push_back(offset);
                elementBufferData.push_back(offset + 2);
                elementBufferData.push_back(offset + 3);

                offset += 4;
            }
        }
    }

    _elementCount = elementBufferData.size();

    glCreateVertexArrays(1, &_vertexArray);
    glCreateBuffers(1, &_vertexBuffer);
    glCreateBuffers(1, &_elementBuffer);

    glNamedBufferData(_vertexBuffer, vertexBufferData.size() * sizeof(float), vertexBufferData.data(), GL_STATIC_DRAW);
    glNamedBufferData(_elementBuffer, elementBufferData.size() * sizeof(uint32_t), elementBufferData.data(), GL_STATIC_DRAW);

    glVertexArrayVertexBuffer(_vertexArray, 0, _vertexBuffer, 0, 5 * sizeof(float));
    glVertexArrayElementBuffer(_vertexArray, _elementBuffer);

    glEnableVertexArrayAttrib(_vertexArray, 0);
    glVertexArrayAttribBinding(_vertexArray, 0, 0);
    glVertexArrayAttribFormat(_vertexArray, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(_vertexArray, 1);
    glVertexArrayAttribBinding(_vertexArray, 1, 0);
    glVertexArrayAttribFormat(_vertexArray, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
}

ChunkMesh::~ChunkMesh()
{
    glDeleteBuffers(1, &_elementBuffer);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteVertexArrays(1, &_vertexArray);
}

void ChunkMesh::Bind() const
{
    glBindVertexArray(_vertexArray);
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

void Renderer::RenderChunkMesh() const
{
    _texture->Bind(0);
    _program->Bind();
    _program->SetUniformMat4(0, _camera.GetViewProjection());
    _program->SetUniformInt(1, 0);
    _chunkMesh->Bind();
    glDrawElements(GL_TRIANGLES, _chunkMesh->GetElementCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::RenderImGui()
{
    ImGui::Text("OpenGL Details:");
    ImGui::Text("Version: %s", _versionName);
    ImGui::Text("Renderer: %s", _rendererName);

    ImGui::Separator();

    _camera.RenderImGui();

    ImGui::Separator();
}

Renderer::Renderer()
    : _camera(glm::vec3(0.0f), glm::radians(80.0f))
{
    gladLoadGL(glfwGetProcAddress);

    _versionName = glGetString(GL_VERSION);
    _rendererName = glGetString(GL_RENDERER);

    glDebugMessageCallback(ApiDebugCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    _program = std::make_shared<ShaderProgram>("assets/default.vert.glsl", "assets/default.frag.glsl");
    _texture = std::make_shared<Texture2D>("assets/texture.png");
    _chunkMesh = std::make_shared<ChunkMesh>(Chunk(glm::ivec2(0, 0)));
}

Renderer::~Renderer()
{
}

void Renderer::ApiDebugCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam)
{
    std::cerr << "[OPENGL] " << message << std::endl;
    assert(severity != GL_DEBUG_SEVERITY_HIGH);
}

} // namespace Krafter
