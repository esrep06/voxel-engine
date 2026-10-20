#pragma once 

#include <GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

namespace gl_layer {
    class vao 
    {  
    public:
        vao();
        ~vao();
        vao(const vao&) = delete;
        vao& operator=(const vao&) = delete;
    
        void generate();
        void bind() const;
        void detach() const;
        void free();

    private: 
        GLuint id = 0;
    };

    class vbo
    {  
    public:
        vbo();
        ~vbo();
        vbo(const vbo&) = delete;
        vbo& operator=(const vbo&) = delete;

        void generate();
        void bind() const;
        void detach() const;
        void send_data(GLsizeiptr size, const void* data, GLenum usage) const;
        void update_data(GLintptr offset, GLsizeiptr size, const void* data) const;
        void free();


    private: 
        GLuint id = 0;
    };

    class ebo 
    {  
    public: 
        ebo();
        ~ebo();
        ebo(const ebo&) = delete;
        ebo& operator=(const ebo&) = delete;

        void generate();
        void bind() const;
        void detach() const;
        void send_data(GLsizeiptr size, const void* data, GLenum usage) const;
        void update_data(GLintptr offset, GLsizeiptr size, const void* data) const;
        void free();

    private: 
        GLuint id = 0;
    };

    void enable_attrib_ptr(GLuint index, GLint size, GLenum type, GLsizei stride, const void* ptr);
    void enable_attrib_array(GLint index);
    void disable_attrib_array(GLint index);

    void draw_indexed(GLenum mode, GLsizei count, GLenum type, const void* indices);
    void draw_simple(GLenum mode, GLint first, GLsizei count);

    void check_gl_errors(const char* stage);
}


