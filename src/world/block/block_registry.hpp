#pragma once 

#include <world/block/block.hpp>

#include <array>
#include <cstdint>

enum class BLOCK_FACE : uint8_t {
    FRONT = 0,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

enum class BLOCK_TEXTURE : uint8_t {
    GRASS_SIDE = 0,
    GRASS_TOP = 1,
    DIRT = 2,
    COBBLESTONE
};

struct block_definition {
    bool solid = false;

    std::array<BLOCK_TEXTURE, 6> textures;
};

class block_registry {
public:
    static const block_definition& get(BLOCK_TYPE type);
private: 
    static const std::array<block_definition, 256> p_definitions; 
};

