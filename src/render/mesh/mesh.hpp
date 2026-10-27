#pragma once 

#include <cstdint>
#include <vector>

#include <core/gl_layer/buffers.hpp>
#include <glm/glm.hpp>

struct vertex {
    float x, y, z;
    float u, v;
};

struct mesh_data {
    std::vector<vertex> vertices;
    std::vector<uint32_t> indices;
};

class mesh {
public:
    mesh() = default;

    mesh(const mesh&) = delete;
    mesh& operator=(const mesh&) = delete;

    mesh(mesh&&) = delete;
    mesh& operator=(mesh&&) = delete;

    void generate(const mesh_data& data);
    void draw() const;

private:
    gl_layer::vao p_vao;
    gl_layer::vbo p_vbo;
    gl_layer::ebo p_ebo;

    GLsizei p_vertex_count = 0;
    GLsizei p_index_count = 0;
};

