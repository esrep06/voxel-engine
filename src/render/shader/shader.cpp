#include <render/shader/shader.hpp>
#include <fstream>
#include <iterator>

shader::shader(std::string vertex, std::string fragment)
: m_vertex_path(vertex), m_fragment_path(fragment)
{}

shader::shader()
{}

uint8_t shader::load_and_compile()
{
    if (m_was_initialized)
        return 1;

    std::ifstream vertex_file(m_vertex_path);
    std::ifstream fragment_file(m_fragment_path);

    if (!vertex_file.is_open() || !fragment_file.is_open()) 
    {
        utilz::logger::log(
            "Could not open shader files: " + m_vertex_path +
            " & " + m_fragment_path + '\n',
            utilz::logger::ERROR
        );

        return 0;
    }

    m_vertex_string.assign(
        std::istreambuf_iterator<char>(vertex_file),
        std::istreambuf_iterator<char>()
    );


    m_fragment_string.assign(
        std::istreambuf_iterator<char>(fragment_file),
        std::istreambuf_iterator<char>()
    );

    utilz::logger::log("Compiling shader: " + m_vertex_path + " & " + m_fragment_path + "...\n");

    uint32_t vertexId, fragmentId;

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_source = m_vertex_string.c_str();
    glShaderSource(vertexId, 1, &vertex_source, nullptr);
    glCompileShader(vertexId);

    int success;
    char log[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexId, 512, NULL, log);
        glDeleteShader(vertexId);
        utilz::logger::log("Shader vertex compilation failed\n", utilz::logger::ERROR);
        fputs(log, stderr);
        return 0;
    }

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragment_source = m_fragment_string.c_str();
    glShaderSource(fragmentId, 1,  &fragment_source, nullptr);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentId, 512, NULL, log);
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
        utilz::logger::log("Shader fragment compilation failed\n", utilz::logger::ERROR);
        fputs(log, stderr);
        return 0;
    }

    m_id = glCreateProgram();

    glAttachShader(m_id, vertexId);
    glAttachShader(m_id, fragmentId);

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, log);
        utilz::logger::log("Shader program link failed\n", utilz::logger::ERROR);
        fputs(log, stderr);

        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
        glDeleteProgram(m_id);
        m_id = 0;

        return 0;
    }

    m_was_initialized = 1;

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    detach();

    utilz::logger::log("Shader compiled successfully!\n", utilz::logger::SUCCESS);

    return 1;
}

void shader::free()
{
    if (!m_was_initialized || m_id == 0) return;

    utilz::logger::log("Freeing shader '" + m_vertex_path + "' memory\n");

    glDeleteProgram(m_id);

    m_id = 0;
    m_was_initialized = 0;
}

void shader::detach()
{
    glUseProgram(0);
}

void shader::use()
{
    glUseProgram(m_id);
}

void shader::send_float(float val, std::string name)
{ 
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), val);
}

void shader::send_mat4(glm::mat4 mat, std::string name)
{ 
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat)); 
}

void shader::send_int(int32_t val, std::string name)
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), val);
}

void shader::send_vec2(float x, float y, std::string name)
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void shader::send_vec3(float x, float y, float z, std::string name)
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

shader::~shader()
{
    free();
}

