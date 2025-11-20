#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    while (Window::Get()->IsOpen())
    {
        Window::Get()->PollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();

        Renderer::Get()->ClearBuffers();
        Renderer::Get()->DrawRgbTriangle();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        Window::Get()->SwapBuffers();
    }
}

Game::Game()
{
    Window::Init();
    Renderer::Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

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