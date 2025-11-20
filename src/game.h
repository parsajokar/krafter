#pragma once

namespace Krafter
{

class Game
{
public:
    static void Init();
    static void Deinit();
    inline static Game* Get() { return _instance; }

    void Run();

private:
    inline static Game* _instance;

    Game();
    ~Game();
};

} // namespace Krafter