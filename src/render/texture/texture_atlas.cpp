#include <render/texture/texture_atlas.hpp>

texture_atlas::texture_atlas(texture* texture, int atlas_width, 
              int atlas_height, int element_width, int element_height)
: p_texture(texture), p_atlas_width(atlas_width), p_atlas_height(atlas_height),

p_element_width(element_width), p_element_height(element_height)
{
    register_element(-1, 3, 3);
}

void texture_atlas::register_element(uint32_t id, int x, int y) {
   if (x * p_element_width > p_atlas_width || x < 0 || 
        y * p_element_height > p_atlas_height || y < 0) 
    {
        utilz::logger::log("Invalid atlas element index...\n");
        return;
    }


    if (!p_element_map.try_emplace(id, utilz::vector2(x, y)).second) 
        utilz::logger::log("Trying to register an already existing atlas element...\n", utilz::logger::ERROR);
}

std::array<utilz::vector2f, 4> texture_atlas::get_uv_coords(uint32_t id) const {
    utilz::vector2 beginning;

    std::array<utilz::vector2f, 4> uvs;

    try {
        beginning = p_element_map.at(id);
    } catch(std::out_of_range& e) 
    {
        std::cerr << "Tried to access non-existing element in texture atlas: " << e.what() << std::endl;
        return get_uv_coords(-1);
    }

    float origin_x = (float)(beginning.x * (float)p_element_width) / (float)p_atlas_width;
    float origin_y = 1 - ((float)(beginning.y * (float)p_element_height) / (float)p_atlas_height);
    float step = ((float)p_element_height / (float)p_atlas_height);

    uvs[0] = utilz::vector2f(origin_x, origin_y ); // top left 
    uvs[1] = utilz::vector2f(origin_x + step, origin_y); // top right
    uvs[2] = utilz::vector2f(origin_x, origin_y - step); // bottom left
    uvs[3] = utilz::vector2f(origin_x + step, origin_y - step); // bottom left

    return uvs;
}

