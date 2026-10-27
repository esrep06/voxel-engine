#include <render/mesh/mesh.hpp>

void mesh::generate(const mesh_data& data) {
    p_vertex_count = static_cast<GLsizei>(data.vertices.size());
    p_index_count = static_cast<GLsizei>(data.indices.size());
    p_vao.generate();
    p_vao.bind();

    p_vbo.generate();
    p_vbo.bind();
    p_vbo.send_data(sizeof(struct vertex) * data.vertices.size(), data.vertices.data(), GL_STATIC_DRAW);

    if (p_index_count > 0) {
        p_ebo.generate();
        p_ebo.bind();

        p_ebo.send_data(sizeof(uint32_t) * data.indices.size(), data.indices.data(), GL_STATIC_DRAW);
    }

    gl_layer::enable_attrib_ptr(0, 3, GL_FLOAT, sizeof(struct vertex), nullptr);
    gl_layer::enable_attrib_array(0);
    gl_layer::enable_attrib_ptr(1, 2, GL_FLOAT, sizeof(struct vertex), (void*)(3 * sizeof(float)));
    gl_layer::enable_attrib_array(1);

    p_vao.detach();
    p_vbo.detach();
}

void mesh::draw() const {
    if (p_vertex_count == 0)
        return;

    p_vao.bind();

    if (p_index_count > 0) {
        gl_layer::draw_indexed(GL_TRIANGLES, p_index_count, GL_UNSIGNED_INT, 0);
    }

    p_vao.detach();
}


