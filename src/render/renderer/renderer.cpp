#include <render/renderer/renderer.hpp>

renderer::renderer() {}

uint8_t renderer::init() {
    utilz::logger::log("Initializing renderer...\n");

    shader* def = p_shader_pool.add_shader("assets/shaders/default_vertex.glsl", 
                             "assets/shaders/default_fragment.glsl", "default");

    texture* grass = p_texture_pool.add_texture("assets/textures/grass.jpg", "grass");


    if (!def || !grass) 
        return 0;

    grass->bind();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float vertices[] = {
        // Front (+Z)
        0.0f,  0.0f,  0.0f, 0.0f, 1.0f, // 0  Top Left
        1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // 1  Top Right
        0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // 2  Bottom Left
        1.0f, -1.0f,  0.0f, 1.0f, 0.0f, // 3  Bottom Right

        // Back (-Z)
        1.0f,  0.0f, -1.0f, 0.0f, 1.0f,// 4  Top Left
        0.0f,  0.0f, -1.0f, 1.0f, 1.0f,// 5  Top Right
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f,// 6  Bottom Left
        0.0f, -1.0f, -1.0f, 1.0f, 0.0f,// 7  Bottom Right

        // Left (-X)
        0.0f,  0.0f, -1.0f, 0.0f, 1.0f,// 8  Top Left
        0.0f,  0.0f,  0.0f, 1.0f, 1.0f,// 9  Top Right
        0.0f, -1.0f, -1.0f, 0.0f, 0.0f,// 10 Bottom Left
        0.0f, -1.0f,  0.0f, 1.0f, 0.0f,// 11 Bottom Right

        // Right (+X)
        1.0f,  0.0f,  0.0f, 0.0f, 1.0f,// 12 Top Left
        1.0f,  0.0f, -1.0f, 1.0f, 1.0f,// 13 Top Right
        1.0f, -1.0f,  0.0f, 0.0f, 0.0f,// 14 Bottom Left
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f,// 15 Bottom Right

        // Top (+Y)
        0.0f,  0.0f, -1.0f, 0.0f, 1.0f,// 16 Top Left
        1.0f,  0.0f, -1.0f, 1.0f, 1.0f,// 17 Top Right
        0.0f,  0.0f,  0.0f, 0.0f, 0.0f,// 18 Bottom Left
        1.0f,  0.0f,  0.0f, 1.0f, 0.0f,// 19 Bottom Right

        // Bottom (-Y)
        0.0f, -1.0f,  0.0f, 0.0f, 1.0f,// 20 Top Left
        1.0f, -1.0f,  0.0f, 1.0f, 1.0f,// 21 Top Right
        0.0f, -1.0f, -1.0f, 0.0f, 0.0f,// 22 Bottom Left
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f// 23 Bottom Right
    };


    unsigned int indices[] = {
        // Front
        0, 1, 2,
        2, 3, 1,

        // Back
        4, 5, 6,
        6, 7, 5,

        // Left
        8, 9, 10,
        10, 11, 9,

        // Right
        12, 13, 14,
        14, 15, 13,

        // Top
        16, 17, 18,
        18, 19, 17,

        // Bottom
        20, 21, 22,
        22, 23, 21
    };

    vao.generate();
    vao.bind();

    vbo.generate(); 
    vbo.bind();
    vbo.send_data(sizeof(vertices), vertices, GL_STATIC_DRAW);

    ebo.generate();
    ebo.bind();
    ebo.send_data(sizeof(indices), indices, GL_STATIC_DRAW);

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
    gl_layer::draw_indexed(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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

