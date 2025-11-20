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
        Renderer::Get()->ClearBuffers();
        Renderer::Get()->DrawRgbTriangle();
        Window::Get()->SwapBuffers();
    }
}

Game::Game()
{
    Window::Init();
    Renderer::Init();
}

Game::~Game()
{
    Renderer::Deinit();
    Window::Deinit();
}

} // namespace Krafter