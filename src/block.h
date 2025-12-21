#pragma once

#include "glm/glm.hpp"

namespace Krafter
{

enum class Block
{
    AIR,
    GRASS
};

class Chunk
{
public:
    constexpr static uint32_t WIDTH = 16;
    constexpr static uint32_t HEIGHT = 256;

    Chunk(const glm::ivec2& position);
    ~Chunk();

    inline const glm::ivec2& GetPosition() const { return _position; }

    const Block& GetBlock(const glm::ivec3& coords) const;
    void SetBlock(const glm::ivec3& coords, Block value);

private:
    glm::ivec2 _position;
    Block* _blocks;
};

} // namespace Krafter
