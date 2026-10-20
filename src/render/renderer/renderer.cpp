#include <render/renderer/renderer.hpp>



renderer::renderer() {}

uint8_t renderer::init() {
    utilz::logger::log("Initializing renderer...\n");

    shader* def = p_shader_pool.add_shader("assets/shaders/default_vertex.glsl", 
                             "assets/shaders/default_fragment.glsl", "default");

    if (!def) 
        return 0;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    }; 

    vao.generate();
    vao.bind();

    vbo.generate(); 
    vbo.bind();
    vbo.send_data(sizeof(vertices), vertices, GL_STATIC_DRAW);

    gl_layer::enable_attrib_ptr(0, 3, GL_FLOAT, 3 * sizeof(float), nullptr);
    gl_layer::enable_attrib_array(0);

    vao.detach();
    vbo.detach();

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
    gl_layer::draw_simple(GL_TRIANGLES, 0, 3);
    vao.detach();
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

