#pragma once 
    
#include <render/shader/shader_pool.hpp>
#include <render/camera/camera.hpp>
#include <core/gl_layer/buffers.hpp>

class renderer {
public: 
    renderer();

    uint8_t init();
    void render(const camera& active_camera);

    gl_layer::vao vao; 
    gl_layer::vbo vbo;

    shader_pool* get_shader_pool();
private: 
    shader_pool p_shader_pool;
    void send_camera(const camera& cam, shader* shader);
};

