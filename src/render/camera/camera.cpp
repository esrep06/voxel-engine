#include <render/camera/camera.hpp>

camera::camera()
{}

camera::camera(utilz::vector3f position, float fov) 
: transform(position, utilz::vector3f(0.0f)), fov(fov)
{}

glm::mat4 camera::get_view_matrix() const {
    glm::vec3 pos = utils::vec3f_to_glm(transform.position);;

    return glm::lookAt(pos, 
                       pos + utils::vec3f_to_glm(transform.forward()), utils::vec3f_to_glm(transform.up()));
}

glm::mat4 camera::get_projection_matrix() const {
    return glm::perspective(glm::radians(fov), p_aspect_ratio, p_near, p_far);
}

