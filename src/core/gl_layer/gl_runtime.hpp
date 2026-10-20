#pragma once

#include <GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>

#include <cpp-utilz/logger/logger.hpp>

class gl_runtime {
public:
    gl_runtime(const gl_runtime&) = delete;
    gl_runtime& operator=(const gl_runtime&) = delete;
    gl_runtime() = default;

    ~gl_runtime();

    uint8_t glfw_initialize();
private: 
    uint8_t p_glfw_initialized = false;

    void gl_terminate();
};


