#include <render/renderer/renderer.hpp>

renderer::renderer() {}

chunk test = chunk(0, -32, 0); 

uint8_t renderer::init() {
    utilz::logger::log("Initializing renderer...\n");

    shader* def = p_shader_pool.add_shader("assets/shaders/default_vertex.glsl", 
                             "assets/shaders/default_fragment.glsl", "default");

    texture* atlas_texture = p_texture_pool.add_texture("assets/textures/atlas.png", "atlas");

    if (!def || !atlas_texture) 
        return 0;

    atlas_texture->bind();
    int atlas_width = 64;
    int atlas_height = 64;
    int altas_element_width = 16;
    int atlas_element_height = 16;

    texture_atlas atlas = texture_atlas(atlas_texture, atlas_width, atlas_height, altas_element_width, atlas_element_height);  

    atlas.register_element(static_cast<int>(BLOCK_TEXTURE::GRASS_SIDE), 0, 0); 
    atlas.register_element(static_cast<int>(BLOCK_TEXTURE::GRASS_TOP), 1, 0);
    atlas.register_element(static_cast<int>(BLOCK_TEXTURE::DIRT), 2, 0);
    atlas.register_element(static_cast<int>(BLOCK_TEXTURE::COBBLESTONE), 3, 0);

    test.build(atlas);
 
    glEnable(GL_DEPTH_TEST);

    return 1;
}

void renderer::render(const camera& active_camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader* default_shader = p_shader_pool.retrieve_shader("default");

    if (!default_shader)
        return;

    default_shader->use();

    send_camera(active_camera, default_shader);

    default_shader->send_mat4(glm::mat4(1.0f), "transform");
    test.draw();
}

void renderer::send_camera(const camera& cam, shader* shader) {
    const glm::mat4 view =
        cam.get_view_matrix();

    const glm::mat4 projection =
        cam.get_projection_matrix();

    // 4. Send camera matrices
    shader->send_mat4(view, "view");
    shader->send_mat4(projection, "projection");
}

shader_pool* renderer::get_shader_pool() {
    return &p_shader_pool;
}

texture_pool* renderer::get_texture_pool() {
    return &p_texture_pool;
}

