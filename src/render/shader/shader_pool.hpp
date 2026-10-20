#pragma once 

#include <map>
#include <cpp-utilz/logger/logger.hpp>
#include <render/shader/shader.hpp>

class shader_pool
{
public:
    shader_pool();

    shader* add_shader(std::string vertex, std::string fragment, std::string identifier);
    void initialize_shaders();

    shader* retrieve_shader(std::string identifier);
    void delete_shader(std::string identifier);

    std::map<std::string, shader>* get_pool();
private:
    std::map<std::string, shader> m_pool;
};

