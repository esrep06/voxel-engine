#pragma once 

#include <core/utils/utils.hpp>
#include <scene/components/transform.hpp>

class camera {
public: 
    camera();
    camera(utilz::vector3f position, float fov);

    glm::mat4 get_view_matrix() const;   
    glm::mat4 get_projection_matrix() const;

    class transform transform;

    float fov = 90.0f;
private: 
    float p_aspect_ratio = 16.0f / 9.0f;
    float p_near = 0.1f; 
    float p_far = 1000.0f;
};

