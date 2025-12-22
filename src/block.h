#pragma once

#include <unordered_map>

#include "glm/glm.hpp"

namespace Krafter
{

enum class Block
{
    AIR,
    DIRT,
    GRASS
};

class BlockAtlas
{
public:
    static void LoadAtlases();
    static const BlockAtlas& GetAtlasOf(Block block);

    static constexpr float STEP = 1.0f / 16.0f;

    glm::vec2 top;
    glm::vec2 side;
    glm::vec2 bottom;

private:
    inline static std::unordered_map<Block, BlockAtlas> _blockAtlases;
};

class Chunk
{
public:
    static constexpr uint32_t WIDTH = 16;
    static constexpr uint32_t HEIGHT = 256;

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
