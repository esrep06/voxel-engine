#pragma once 

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cpp-utilz/math/vector3.hpp>

class camera {
public: 
    camera();
    camera(utilz::vector3f position, float fov);

    glm::mat4 get_view_matrix() const;   
    glm::mat4 get_projection_matrix() const;
    utilz::vector3f front = utilz::vector3f(0.0f, 0.0f, -1.0f);

    utilz::vector3f position = utilz::vector3f(0.0f, 0.0f, 0.0f);
    float fov = 90.0f;
private: 
    float p_aspect_ratio = 16.0f / 9.0f;
    float p_near = 0.1f; 
    float p_far = 1000.0f;
};

