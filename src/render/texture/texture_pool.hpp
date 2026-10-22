#pragma once

#include <map>
#include <cpp-utilz/logger/logger.hpp>

#include <render/texture/texture.hpp>

class texture_pool
{
public:
    texture_pool();

    texture* add_texture(std::string path, std::string identifier);
    void initialize_textures();

    texture* retrieve_texture(std::string identifier);
    void delete_texture(std::string identifier);

    std::map<std::string, texture>* get_pool();
private:
    std::map<std::string, texture> m_pool;
};

