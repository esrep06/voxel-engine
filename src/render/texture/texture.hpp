#pragma once

#include <string> 
#include <stdexcept>

#include <glew/include/GL/glew.h>

#include <stb_image/stb_image.h>

#include <cpp-utilz/logger/logger.hpp>

class texture 
{
public:
    texture(const texture&) = delete;
    texture& operator=(const texture&) = delete;
    texture(std::string path);
    ~texture();

    void load();
    uint32_t get_id();
    void bind();
    void detach();
    std::string get_path();
    int32_t get_width();
    int32_t get_height();
    int32_t get_channels();
    uint8_t* get_data();
    void free();
private:
    int32_t m_width = 0, m_height = 0, m_channels = 0;
    uint32_t m_id = 0;
    std::string m_path;
    uint8_t m_loaded = 0;
    uint8_t* m_data = nullptr;
};

