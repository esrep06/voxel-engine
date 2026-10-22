#include <render/texture/texture.hpp>

texture::texture(std::string path)
: m_path(path)
{}

void texture::load()
{
    if (m_loaded) 
        return;

    utilz::logger::log("Loading texture: " + m_path + '\n');

    stbi_set_flip_vertically_on_load(1);	

    m_data = stbi_load(
        m_path.c_str(), 
        &m_width, &m_height, 
        &m_channels, 
        0);

    if (!m_data)
    {
        utilz::logger::log(
            "Failed to load texture\n    File exists? -> " + 
            m_path + 
            '\n', 
            utilz::logger::ERROR);

        throw std::runtime_error("Failed to load texture: " + m_path);
    }
    else 
{
        // Generate and bind texture
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        // Set texture parameters of currently bound texture
        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, 
                        GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        switch (m_channels)
        {
            case 3:
                {
                    GLint previous_alignment = 0;
                    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previous_alignment);

                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                    glTexImage2D(
                        GL_TEXTURE_2D, 0, GL_RGB,
                        m_width, m_height, 0,
                        GL_RGB, GL_UNSIGNED_BYTE, m_data
                    );

                    glPixelStorei(GL_UNPACK_ALIGNMENT, previous_alignment);

                    glGenerateMipmap(GL_TEXTURE_2D);
                    break;
                }
            case 4:
                {
                    GLint previous_alignment = 0;
                    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previous_alignment);

                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                    glTexImage2D(
                        GL_TEXTURE_2D, 0, GL_RGBA8,
                        m_width, m_height, 0,
                        GL_RGBA, GL_UNSIGNED_BYTE, m_data
                    );

                    glPixelStorei(GL_UNPACK_ALIGNMENT, previous_alignment);

                    glGenerateMipmap(GL_TEXTURE_2D);
                    break;
                }
            default:
                utilz::logger::log("Error loading texture\n Unknown file format: " + m_path + '\n', utilz::logger::ERROR);

                const int channels = m_channels;

                glBindTexture(GL_TEXTURE_2D, 0);
                free();

                throw std::runtime_error(
                    "Unsupported texture channel count (" + 
                    std::to_string(channels) + "): " + m_path);
                break;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // We can free the texture data, wont be using it anymore
    /* delete m_data; */

    utilz::logger::log("Texture loaded sucessfully!\n", utilz::logger::SUCCESS);

    m_loaded = 1;

}

uint32_t texture::get_id()
{ return m_id; }


void texture::bind()
{ glBindTexture(GL_TEXTURE_2D, m_id); }
void texture::detach()
{ glBindTexture(GL_TEXTURE_2D, 0); }

std::string texture::get_path()
{ return m_path; }

int32_t texture::get_width()
{ return m_width; }

int32_t texture::get_height()
{ return m_height; }

int32_t texture::get_channels()
{ return m_channels; }

uint8_t* texture::get_data() 
{ return m_data; }

void texture::free()
{
    if (m_id != 0)
    {
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }

    stbi_image_free(m_data);
    m_data = nullptr;

    m_width = 0;
    m_height = 0;
    m_channels = 0;
    m_loaded = 0;

    utilz::logger::log("Freeing texture: " + m_path + '\n');
}

texture::~texture()
{
    free();
}
