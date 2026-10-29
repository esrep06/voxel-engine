#include <world/chunk/chunk_mesher.hpp>

using face_vertices = std::array<glm::vec3, 4>;

static const std::array<face_vertices, 6> FACE_VERTICES = {{
    // FRONT (-Z)
    {{{0, 0, 0}, {1, 0, 0}, {0, -1, 0}, {1, -1, 0}}},

    // BACK (+Z)
    {{{1, 0, 1}, {0, 0, 1}, {1, -1, 1}, {0, -1, 1}}},

    // LEFT (-X)
    {{{0, 0, 1}, {0, 0, 0}, {0, -1, 1}, {0, -1, 0}}},

    // RIGHT (+X)
    {{{1, 0, 0}, {1, 0, 1}, {1, -1, 0}, {1, -1, 1}}},

    // TOP (+Y)
    {{{0, 0, 1}, {1, 0, 1}, {0, 0, 0}, {1, 0, 0}}},

    // BOTTOM (-Y)
    {{{0, -1, 0}, {1, -1, 0}, {0, -1, 1}, {1, -1, 1}}}
}};

void chunk_mesher::generate_face(
    mesh_data* data,
    BLOCK_TYPE type,
    BLOCK_FACE face,
    const texture_atlas& atlas,
    int x, int y, int z
) {
    const block_definition& definition =
        block_registry::get(type);

    const size_t face_index = static_cast<size_t>(face);

    BLOCK_TEXTURE texture = definition.textures[face_index];

    auto uvs = atlas.get_uv_coords(
        static_cast<uint32_t>(texture)
    );

    const auto& positions = FACE_VERTICES[face_index];

    uint32_t base = static_cast<uint32_t>(
        data->vertices.size()
    );

    for (size_t i = 0; i < 4; ++i) {
        const glm::vec3& p = positions[i];

        data->vertices.push_back({
            .x = x + p.x,
            .y = y + p.y,
            .z = z + p.z,
            .u = uvs[i].x,
            .v = uvs[i].y
        });
    }

    constexpr uint32_t indices[] = {
        0, 1, 2,
        2, 3, 1
    };

    for (uint32_t index : indices) {
        data->indices.push_back(base + index);
    }
}

mesh_data chunk_mesher::generate(const chunk& source, const texture_atlas& atlas) {
    mesh_data data;

     for (int x = 0; x < source.CHUNK_SIZE_X; x++) {
        for (int z = 0; z < source.CHUNK_SIZE_Z; z++) {
          for (int y = 0; y < source.CHUNK_SIZE_Y; y++) {
                BLOCK_TYPE type = source.get_block(x, y, z);

                if (type == BLOCK_TYPE::AIR) continue;

                std::array<BLOCK_TYPE, 6> neighbors = source.get_block_neighbors(x, y, z);

                for (int i = 0; i < static_cast<int>(neighbors.size()); i++)
                {
                    if (neighbors[i] == BLOCK_TYPE::AIR) {
                        generate_face(&data, type, static_cast<BLOCK_FACE>(i), atlas, x + source.get_origin().x, y + source.get_origin().y, z + source.get_origin().z);
                    }
                }
            }
        }
    }

    for (int i = 0; i < source.CHUNK_SIZE_X * source.CHUNK_SIZE_Z * source.CHUNK_SIZE_Y; i++) {
        int e_cursor = i * 24;
    
        data.indices.push_back(e_cursor + 0);
        data.indices.push_back(e_cursor + 1);
        data.indices.push_back(e_cursor + 2);
        data.indices.push_back(e_cursor + 2);
        data.indices.push_back(e_cursor + 3);
        data.indices.push_back(e_cursor + 1);
    
        data.indices.push_back(e_cursor + 4);
        data.indices.push_back(e_cursor + 5);
        data.indices.push_back(e_cursor + 6);
        data.indices.push_back(e_cursor + 6);
        data.indices.push_back(e_cursor + 7);
        data.indices.push_back(e_cursor + 5);
    
        data.indices.push_back(e_cursor + 8);
        data.indices.push_back(e_cursor + 9);
        data.indices.push_back(e_cursor + 10);
        data.indices.push_back(e_cursor + 10);
        data.indices.push_back(e_cursor + 11);
        data.indices.push_back(e_cursor + 9);
    
        data.indices.push_back(e_cursor + 12);
        data.indices.push_back(e_cursor + 13);
        data.indices.push_back(e_cursor + 14);
        data.indices.push_back(e_cursor + 14);
        data.indices.push_back(e_cursor + 15);
        data.indices.push_back(e_cursor + 13);
    
        data.indices.push_back(e_cursor + 16);
        data.indices.push_back(e_cursor + 17);
        data.indices.push_back(e_cursor + 18);
        data.indices.push_back(e_cursor + 18);
        data.indices.push_back(e_cursor + 19);
        data.indices.push_back(e_cursor + 17);
    
        data.indices.push_back(e_cursor + 20);
        data.indices.push_back(e_cursor + 21);
        data.indices.push_back(e_cursor + 22);
        data.indices.push_back(e_cursor + 22);
        data.indices.push_back(e_cursor + 23);
        data.indices.push_back(e_cursor + 21);
    }

    return data;
}



