#include "block.h"

namespace Krafter
{

Chunk::Chunk(const glm::ivec2& position)
    : _position(position)
{
    _blocks = new Block[WIDTH * WIDTH * HEIGHT];
}

Chunk::~Chunk()
{
    delete[] _blocks;
}

const Block& Chunk::GetBlock(const glm::ivec3& coords) const
{
    return _blocks[(coords.y * WIDTH * WIDTH) + (coords.z * WIDTH) + coords.x];
}

void Chunk::SetBlock(const glm::ivec3& coords, Block value)
{
    _blocks[(coords.y * WIDTH * WIDTH) + (coords.z * WIDTH) + coords.x] = value;
}

} // namespace Krafter
