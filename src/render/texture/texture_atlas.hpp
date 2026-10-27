#pragma once 

#include <render/texture/texture.hpp>
#include <unordered_map>
#include <array>
#include <cpp-utilz/math/vector2.hpp>
#include <cpp-utilz/logger/logger.hpp>

class texture_atlas {
public:
    texture_atlas(texture* texture, int atlas_width, 
                  int atlas_height, int element_width, int element_height);

    // top left, top right, bottom left, bottom right
    std::array<utilz::vector2f, 4> get_uv_coords(uint32_t id) const;

    // x and y index in atlas 
    void register_element(uint32_t id, int x, int y);
private: 
    texture* p_texture = nullptr;

    std::unordered_map<int32_t, utilz::vector2> p_element_map;

    int p_atlas_width = 0; 
    int p_atlas_height = 0;
    int p_element_width = 0;
    int p_element_height = 0;
};

