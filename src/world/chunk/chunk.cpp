#include <world/chunk/chunk.hpp>

chunk::chunk(int x, int y, int z)
:p_blocks(CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z), p_origin(x, y, z) {
    for (int _x = x; _x < CHUNK_SIZE_X; _x++) {
        for (int _z = z; _z < CHUNK_SIZE_Z; _z++) {
            for (int _y = y; _y < CHUNK_SIZE_Y; _y++) {
                set_block(BLOCK_TYPE::GRASS, _x, _y, _z);
            }
        }
    }
}

BLOCK_TYPE chunk::get_block(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0 ||
        x > CHUNK_SIZE_X || y > CHUNK_SIZE_Y || z > CHUNK_SIZE_Z) {
        return BLOCK_TYPE::AIR;
    }

    return p_blocks[(z * CHUNK_SIZE_X * CHUNK_SIZE_Y) + (y * CHUNK_SIZE_X) + x];
}

void chunk::set_block(BLOCK_TYPE type, int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0 ||
        x > CHUNK_SIZE_X || y > CHUNK_SIZE_Y || z > CHUNK_SIZE_Z) {
        return;
    }

    p_blocks[(z * CHUNK_SIZE_X * CHUNK_SIZE_Y) + (y * CHUNK_SIZE_X) + x] = type;
}

utilz::vector3f chunk::get_origin() const {
    return p_origin;
}

