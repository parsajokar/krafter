#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glm/gtc/type_ptr.hpp"

#include "window.h"
#include "renderer.h"
#include "game.h"

namespace Krafter
{

void Game::Init()
{
    _instance = new Game();
}

void Game::Deinit()
{
    delete _instance;
}

void Game::Run()
{
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    float lastFrameTime = 0.0f;

    while (Window::Get()->IsOpen())
    {
        Window::Get()->PollEvents();
        if (Window::Get()->IsKeyDown(Key::Escape))
        {
            Window::Get()->Close();
        }

        float currentFrameTime = Window::Get()->GetTime();
        _delta = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        Renderer::Get()->GetCamera().Update();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        ImGui::SliderFloat("Camera Speed", &Renderer::Get()->GetCamera().speed, 1.0f, 100.0f);
        ImGui::SliderFloat("Camera Sensitivity", &Renderer::Get()->GetCamera().sensitivity, 0.1f, 10.0f);
        ImGui::NewLine();
        ImGui::ColorPicker4("Rectangle Color", glm::value_ptr(color));
        ImGui::End();

        ImGui::Render();

        Renderer::Get()->ClearBuffers();
        Renderer::Get()->DrawRectangle(color);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        Window::Get()->SwapBuffers();
    }
}

Game::Game()
    : _delta(0.0f)
{
    Window::Init();
    Renderer::Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = "assets/editorconfig.ini";

    ImGui_ImplGlfw_InitForOpenGL(Window::Get()->GetId(), true);
    ImGui_ImplOpenGL3_Init("#version 450 core");

}

Game::~Game()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Renderer::Deinit();
    Window::Deinit();
}

} // namespace Krafter
