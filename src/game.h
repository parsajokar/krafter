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
    inline float GetDelta() const { return _delta; };

private:
    inline static Game* _instance;

    Game();
    ~Game();

    float _delta;
};

} // namespace Krafter