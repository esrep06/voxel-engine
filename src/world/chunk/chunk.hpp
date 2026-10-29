#pragma once 

#include <world/block/block.hpp>
#include <world/chunk/chunk_data.hpp>
#include <vector>
#include <cpp-utilz/math/vector3.hpp>
#include <render/texture/texture_atlas.hpp>
#include <world/chunk/chunk_mesher.hpp>

class chunk_mesher;

class chunk {
public:
    static const int CHUNK_SIZE_X = 16;
    static const int CHUNK_SIZE_Y = 32;
    static const int CHUNK_SIZE_Z = 16;

    chunk(int origin_x, int origin_y, int origin_z);
    void build(const texture_atlas& atlas);
    void draw();

    BLOCK_TYPE get_block(int x, int y, int z) const;

    void set_block(BLOCK_TYPE type, int x, int y, int z);

    // Goes front back left right top bottom 
    std::array<BLOCK_TYPE, 6> get_block_neighbors(int x, int y, int z) const; 

    utilz::vector3f get_origin() const;
private:
    chunk_data p_data;
    std::vector<BLOCK_TYPE> p_blocks;
    utilz::vector3f p_origin;
};
