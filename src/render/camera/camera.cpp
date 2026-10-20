#include <render/camera/camera.hpp>

camera::camera()
{}

camera::camera(utilz::vector3f position, float fov) 
: position(position), fov(fov)
{}

glm::mat4 camera::get_view_matrix() const {
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 pos = glm::vec3(position.x, position.y, position.z);

    return glm::lookAt(pos, pos + glm::vec3(front.x, front.y, front.z), up);
}

glm::mat4 camera::get_projection_matrix() const {
    return glm::perspective(glm::radians(fov), p_aspect_ratio, p_near, p_far);
}

