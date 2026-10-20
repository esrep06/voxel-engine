#include <core/gl_layer/buffers.hpp>
#include <iostream>

namespace gl_layer
{
    // VBO

    vbo::vbo()
    {}  
    
    vbo::~vbo() { free(); }

    void vbo::generate() 
    {
        if (id != 0) { return; } 

        glGenBuffers(1, &id); 
    }

    void vbo::bind() const
    { glBindBuffer(GL_ARRAY_BUFFER, id); }

    void vbo::detach() const
    { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void vbo::send_data(GLsizeiptr size, const void* data, GLenum usage) const
    { glBufferData(GL_ARRAY_BUFFER, size, data, usage); }

    void vbo::update_data(GLintptr offset, GLsizeiptr size, const void* data) const 
    { glBufferSubData(GL_ARRAY_BUFFER, offset, size, data); }

    void vbo::free()
    { if (id == 0) return; glDeleteBuffers(1, &id); id = 0;}


    // VAO 

    vao::vao()
    { }

    vao::~vao() { free(); }


    void vao::generate()
    {

        if (id != 0) { return; }

        glGenVertexArrays(1, &id);
    }

    void vao::bind() const
    { glBindVertexArray(id); }

    void vao::detach() const
    { glBindVertexArray(0); }

    void vao::free()
    { if (id == 0) return; glDeleteVertexArrays(1, &id); id = 0;}

    // EBO

    ebo::ebo() 
    {}
    ebo::~ebo() { free(); }

    void ebo::generate()
    { 
        if (id != 0) return

        glGenBuffers(1, &id); 
    }

    void ebo::bind() const
    { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

    void ebo::detach() const
    { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    void ebo::send_data(GLsizeiptr size, const void* data, GLenum usage) const
    { glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage); }

    void ebo::update_data(GLintptr offset, GLsizeiptr size, const void* data) const
    { glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data); }

    void ebo::free()
    { if (id == 0) return; glDeleteBuffers(1, &id); id = 0; }

    void enable_attrib_ptr(GLuint index, GLint size, GLenum type, GLsizei stride, const void* ptr)
    { glVertexAttribPointer(index, size, type, GL_FALSE, stride, ptr); }

    void enable_attrib_array(GLint index)
    { glEnableVertexAttribArray(index); }

    void disable_attrib_array(GLint index)
    { glDisableVertexAttribArray(index); }

    void draw_indexed(GLenum mode, GLsizei count, GLenum type, const void* indices)
    { glDrawElements(mode, count, type, indices); }

    void draw_simple(GLenum mode, GLint first, GLsizei count)
    { glDrawArrays(mode, first, count); }

    void check_gl_errors(const char* stage) {
        GLenum error;

        while ((error = glGetError()) != GL_NO_ERROR) {
            std::cerr << "[OpenGL Error] "
                      << stage
                      << " : 0x"
                      << std::hex << error
                      << std::dec << '\n';
        }
    }
}

