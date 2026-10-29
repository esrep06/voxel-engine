#include <world/chunk/chunk.hpp>

chunk::chunk(int origin_x, int origin_y, int origin_z)
:p_blocks(CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z), p_origin(origin_x, origin_y, origin_z) {
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            for (int y = 0; y < CHUNK_SIZE_Y; y++) {
                BLOCK_TYPE current_type = BLOCK_TYPE::GRASS; 

                if (y < CHUNK_SIZE_Y - 1) 
                    current_type = BLOCK_TYPE::DIRT;

                if (y < (int)(CHUNK_SIZE_Y / 2))
                    current_type = BLOCK_TYPE::COBBLESTONE;

                set_block(current_type, x, y, z);
            }
        }
    }
}

void chunk::build(const texture_atlas& atlas) {
    p_data.p_mesh.generate(chunk_mesher::generate(*this, atlas));
}

void chunk::draw() {
    p_data.p_mesh.draw();
}

BLOCK_TYPE chunk::get_block(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0 ||
        x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z) {
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

std::array<BLOCK_TYPE, 6> chunk::get_block_neighbors(int x, int y, int z) const {
    return {get_block(x, y, z - 1), get_block(x, y, z + 1), get_block(x - 1, y, z), 
            get_block(x + 1, y, z), get_block(x, y + 1, z), get_block(x, y - 1, z)};
}

