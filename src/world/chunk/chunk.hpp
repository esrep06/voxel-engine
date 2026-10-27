#pragma once 

#include <world/block/block.hpp>
#include <world/chunk/chunk_data.hpp>
#include <vector>
#include <cpp-utilz/math/vector3.hpp>

class chunk {
public:
    static const int CHUNK_SIZE_X = 16;
    static const int CHUNK_SIZE_Y = 32;
    static const int CHUNK_SIZE_Z = 16;

    chunk(int x, int y, int z);

    BLOCK_TYPE get_block(int x, int y, int z) const;

    void set_block(BLOCK_TYPE type, int x, int y, int z);

    utilz::vector3f get_origin() const;
    chunk_data data;
private:
    std::vector<BLOCK_TYPE> p_blocks;
    utilz::vector3f p_origin;
};
