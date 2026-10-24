#include <render/renderer/renderer.hpp>

renderer::renderer() {}

uint8_t renderer::init() {
    utilz::logger::log("Initializing renderer...\n");

    shader* def = p_shader_pool.add_shader("assets/shaders/default_vertex.glsl", 
                             "assets/shaders/default_fragment.glsl", "default");

    texture* atlas_texture = p_texture_pool.add_texture("assets/textures/atlas.png", "atlas");

    if (!def || !atlas_texture) 
        return 0;

    atlas_texture->bind();

    texture_atlas atlas = texture_atlas(atlas_texture, 64, 64, 16, 16);   
    atlas.register_element("grass_face", 0, 0);
    atlas.register_element("grass_top", 1, 0);
    atlas.register_element("dirt", 2, 0);
    
    std::array<utilz::vector2f, 4> uvs = atlas.get_uv_coords("grass_face");
    std::array<utilz::vector2f, 4> top = atlas.get_uv_coords("grass_top");
    std::array<utilz::vector2f, 4> dirt = atlas.get_uv_coords("dirt");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    const int X_SIZE = 16; 
    const int Z_SIZE = 16; 
    const int Y_SIZE = 32;
    const int BLOCK_NUM = X_SIZE * Z_SIZE * Y_SIZE;
    const int FACES = 6;
    const int VERTICES_PER_FACE = 4;

    const int INDICES_PER_FACE = 6;

    struct vertex {
        float x, y, z;
        float u, v;
    };

    struct vertex* vertices = new vertex[FACES * VERTICES_PER_FACE * BLOCK_NUM];

    unsigned int* indices = new unsigned int[INDICES_PER_FACE * FACES * BLOCK_NUM];

    int v_cursor = 0;

    for (int x = 0; x < X_SIZE; x++) {
        for (int z = 0; z < Z_SIZE; z++) {
            for (int y = 0; y < Y_SIZE; y++) {
                vertices[v_cursor + 0] = {.x = x + 0.0f, .y = y + 0.0f, .z = z + 0.0f, .u = uvs[0].x, .v = uvs[0].y}; 
                vertices[v_cursor + 1] = {.x = x + 1.0f, .y = y + 0.0f, .z = z + 0.0f, .u = uvs[1].x, .v = uvs[1].y};
                vertices[v_cursor + 2] = {.x = x + 0.0f, .y = y - 1.0f, .z = z + 0.0f, .u = uvs[2].x, .v = uvs[2].y};
                vertices[v_cursor + 3] = {.x = x + 1.0f, .y = y - 1.0f, .z = z + 0.0f, .u = uvs[3].x, .v = uvs[3].y};

                vertices[v_cursor + 4] = {.x = x + 1.0f, .y = y + 0.0f, .z =  z + 1.0f, .u = uvs[0].x, .v = uvs[0].y}; 
                vertices[v_cursor + 5] = {.x = x + 0.0f, .y = y + 0.0f, .z = z + 1.0f, .u = uvs[1].x, .v = uvs[1].y};
                vertices[v_cursor + 6] = {.x = x + 1.0f, .y = y - 1.0f, .z = z + 1.0f, .u = uvs[2].x, .v = uvs[2].y};
                vertices[v_cursor + 7] = {.x = x + 0.0f, .y = y - 1.0f, .z = z + 1.0f, .u = uvs[3].x, .v = uvs[3].y};

                vertices[v_cursor + 8] =  {.x = x + 0.0f, .y = y + 0.0f, .z = z + 1.0f, .u = uvs[0].x, .v = uvs[0].y}; 
                vertices[v_cursor + 9] =  {.x = x + 0.0f, .y = y + 0.0f, .z = z + 0.0f, .u = uvs[1].x, .v = uvs[1].y};
                vertices[v_cursor + 10] = {.x = x + 0.0f, .y = y - 1.0f, .z = z + 1.0f, .u = uvs[2].x, .v = uvs[2].y};
                vertices[v_cursor + 11] = {.x = x + 0.0f, .y = y - 1.0f, .z = z + 0.0f, .u = uvs[3].x, .v = uvs[3].y};

                vertices[v_cursor + 12] = {.x = x + 1.0f, .y = y + 0.0f, .z = z + 0.0f, .u = uvs[0].x, .v = uvs[0].y}; 
                vertices[v_cursor + 13] = {.x = x + 1.0f, .y = y + 0.0f, .z = z + 1.0f, .u = uvs[1].x, .v = uvs[1].y};
                vertices[v_cursor + 14] = {.x = x + 1.0f, .y = y - 1.0f, .z = z + 0.0f, .u = uvs[2].x, .v = uvs[2].y};
                vertices[v_cursor + 15] = {.x = x + 1.0f, .y = y - 1.0f, .z = z + 1.0f, .u = uvs[3].x, .v = uvs[3].y};

                vertices[v_cursor + 16] = {.x = x + 0.0f, .y = y + 0.0f, .z = z + 1.0f, .u = top[0].x, .v = top[0].y}; 
                vertices[v_cursor + 17] = {.x = x + 1.0f, .y = y + 0.0f, .z = z + 1.0f, .u = top[1].x, .v = top[1].y};
                vertices[v_cursor + 18] = {.x = x + 0.0f, .y = y + 0.0f, .z = z + 0.0f, .u = top[2].x, .v = top[2].y};
                vertices[v_cursor + 19] = {.x = x + 1.0f, .y = y + 0.0f, .z = z + 0.0f, .u = top[3].x, .v = top[3].y};

                vertices[v_cursor + 20] = {.x = x + 0.0f, .y = y - 1.0f, .z = z + 0.0f, .u = dirt[0].x, .v = dirt[0].y}; 
                vertices[v_cursor + 21] = {.x = x + 1.0f, .y = y - 1.0f, .z = z + 0.0f , .u = dirt[1].x, .v = dirt[1].y};
                vertices[v_cursor + 22] = {.x = x + 0.0f, .y = y - 1.0f, .z = z + 1.0f, .u = dirt[2].x, .v = dirt[2].y};
                vertices[v_cursor + 23] = {.x = x + 1.0f, .y = y - 1.0f, .z = z + 1.0f, .u = dirt[3].x, .v = dirt[3].y};

                v_cursor += 24;
            }
        }
    }

    int i_cursor = 0;

    for (int i = 0; i < BLOCK_NUM; i++) {
        int e_cursor = i * 24;

        indices[i_cursor + 0] = e_cursor + 0;
        indices[i_cursor + 1] = e_cursor + 1;
        indices[i_cursor + 2] = e_cursor + 2;
        indices[i_cursor + 3] = e_cursor + 2;
        indices[i_cursor + 4] = e_cursor + 3;
        indices[i_cursor + 5] = e_cursor + 1;

        indices[i_cursor + 6] = e_cursor  + 4;
        indices[i_cursor + 7] = e_cursor  + 5;
        indices[i_cursor + 8] = e_cursor  + 6;
        indices[i_cursor + 9] = e_cursor  + 6;
        indices[i_cursor + 10] = e_cursor + 7;
        indices[i_cursor + 11] = e_cursor + 5;

        indices[i_cursor + 12] = e_cursor + 8;
        indices[i_cursor + 13] = e_cursor + 9;
        indices[i_cursor + 14] = e_cursor + 10;
        indices[i_cursor + 15] = e_cursor + 10;
        indices[i_cursor + 16] = e_cursor + 11;
        indices[i_cursor + 17] = e_cursor + 9;

        indices[i_cursor + 18] = e_cursor + 12;
        indices[i_cursor + 19] = e_cursor + 13;
        indices[i_cursor + 20] = e_cursor + 14;
        indices[i_cursor + 21] = e_cursor + 14;
        indices[i_cursor + 22] = e_cursor + 15;
        indices[i_cursor + 23] = e_cursor + 13;

        indices[i_cursor + 24] = e_cursor + 16;
        indices[i_cursor + 25] = e_cursor + 17;
        indices[i_cursor + 26] = e_cursor + 18;
        indices[i_cursor + 27] = e_cursor + 18;
        indices[i_cursor + 28] = e_cursor + 19;
        indices[i_cursor + 29] = e_cursor + 17;

        indices[i_cursor + 30] = e_cursor + 20;
        indices[i_cursor + 31] = e_cursor + 21;
        indices[i_cursor + 32] = e_cursor + 22;
        indices[i_cursor + 33] = e_cursor + 22;
        indices[i_cursor + 34] = e_cursor + 23;
        indices[i_cursor + 35] = e_cursor + 21;

        i_cursor += 36;
    }

    vao.generate();
    vao.bind();

    vbo.generate(); 
    vbo.bind();
    vbo.send_data(sizeof(vertex) * VERTICES_PER_FACE * FACES * BLOCK_NUM, vertices, GL_STATIC_DRAW);

    ebo.generate();
    ebo.bind();
    ebo.send_data(sizeof(unsigned int) * INDICES_PER_FACE * FACES * BLOCK_NUM, indices, GL_STATIC_DRAW);

    gl_layer::enable_attrib_ptr(0, 3, GL_FLOAT, 5 * sizeof(float), nullptr);
    gl_layer::enable_attrib_ptr(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    gl_layer::enable_attrib_array(0);
    gl_layer::enable_attrib_array(1);

    vao.detach();

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

    vao.bind();
    gl_layer::draw_indexed(GL_TRIANGLES, 16 * 16 * 32 * 36, GL_UNSIGNED_INT, 0);
    // gl_layer::draw_simple(GL_TRIANGLES, 0, 3);
    ebo.bind();
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

