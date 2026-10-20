#pragma once 

#include <string> 
#include <inttypes.h>

#include <core/gl_layer/gl_runtime.hpp>
#include <cpp-utilz/color/color.hpp>
#include <core/input/input.hpp>

class window {
public: 
    window(std::string title, uint16_t width, uint16_t height, utilz::rgba_color color);
    // Prevents copying 
    window(const window&) = delete;
    window& operator=(const window&) = delete;

    uint8_t create();

    GLFWwindow* get_window() const;

    uint8_t should_close();

    void clearColor();

    ~window();
private:
    uint8_t glew_create();
    void set_callbacks();

    uint8_t p_window_initialized = false;
    uint8_t p_glew_initialized = false;
    GLFWwindow* p_window = nullptr;

    std::string p_title = "GLFW Window";
    uint16_t p_width = 800;
    uint16_t p_height = 600;
    utilz::rgba_color p_color = {255, 255, 255, 255};
};

