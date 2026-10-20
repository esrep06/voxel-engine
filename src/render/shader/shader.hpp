#pragma once 

#include <string>
#include <cstdint>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cpp-utilz/logger/logger.hpp>

class shader 
{
public:
    shader(const shader&) = delete;
    shader& operator=(const shader&) = delete;

    shader(std::string vertex, std::string fragment);
    shader();
    ~shader();

    uint8_t load_and_compile();

    void use();
    void detach();

    void send_float(float val, std::string varName);
    void send_mat4(glm::mat4 mat, std::string name);
    void send_int(int32_t val, std::string name);
    void send_vec2(float x, float y, std::string name);
    void send_vec3(float x, float y, float z, std::string name);

    void free();
private:
    GLuint m_id = 0;

    std::string m_vertex_string, m_fragment_string, m_vertex_path, m_fragment_path;

    uint8_t m_was_initialized = 0;
};

