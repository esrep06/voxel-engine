#pragma once 

#include <world/chunk/chunk.hpp>
#include <world/block/block_registry.hpp>
#include <render/mesh/mesh.hpp>
#include <render/texture/texture_atlas.hpp>
#include <render/mesh/mesh.hpp>

class chunk;

class chunk_mesher {
public: 
    static mesh_data generate(const chunk& source, const texture_atlas& atlas);

private: 
     // void generate_face(mesh_data* data, BLOCK_TYPE type, BLOCK_FACE face, const texture_atlas& atlas, int x, int y, int z);
    static void generate_face(mesh_data* data, BLOCK_TYPE type, BLOCK_FACE face, const texture_atlas& atlas, int x, int y, int z);
};

