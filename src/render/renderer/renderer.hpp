#pragma once 
    
#include <render/shader/shader_pool.hpp>
#include <render/texture/texture_pool.hpp>
#include <render/camera/camera.hpp>
#include <render/texture/texture_atlas.hpp>
#include <core/gl_layer/buffers.hpp>

class renderer {
public: 
    renderer();

    uint8_t init();
    void render(const camera& active_camera);

    gl_layer::vao vao; 
    gl_layer::vbo vbo;
    gl_layer::ebo ebo;

    shader_pool* get_shader_pool();
    texture_pool* get_texture_pool();
private: 
    shader_pool p_shader_pool;
    texture_pool p_texture_pool;

    void send_camera(const camera& cam, shader* shader);
};

