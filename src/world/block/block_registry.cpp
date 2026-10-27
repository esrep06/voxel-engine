#include <world/block/block_registry.hpp>

const std::array<block_definition, 256>
block_registry::p_definitions = [] {
    std::array<block_definition, 256> definitions{};

    definitions[static_cast<uint8_t>(BLOCK_TYPE::AIR)] = {
        .solid = false,
        .textures = {}
    };

    definitions[static_cast<uint8_t>(BLOCK_TYPE::GRASS)] = {
        .solid = true,
        .textures = {
            BLOCK_TEXTURE::GRASS_SIDE,
            BLOCK_TEXTURE::GRASS_SIDE,
            BLOCK_TEXTURE::GRASS_SIDE,
            BLOCK_TEXTURE::GRASS_SIDE,
            BLOCK_TEXTURE::GRASS_TOP,
            BLOCK_TEXTURE::DIRT
        }
    };

    definitions[static_cast<uint8_t>(BLOCK_TYPE::DIRT)] = {
        .solid = true,
        .textures = {
            BLOCK_TEXTURE::DIRT,
            BLOCK_TEXTURE::DIRT,
            BLOCK_TEXTURE::DIRT,
            BLOCK_TEXTURE::DIRT,
            BLOCK_TEXTURE::DIRT,
            BLOCK_TEXTURE::DIRT
        }
    };

    return definitions;
}();

const block_definition& block_registry::get(BLOCK_TYPE type) {
    return p_definitions[static_cast<uint8_t>(type)];
}

