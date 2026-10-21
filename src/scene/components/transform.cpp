#include <scene/components/transform.hpp>

transform::transform(utilz::vector3f position, utilz::vector3f scale)
: position(position), scale(scale) 
{}

transform::transform()
{}

glm::mat4 transform::get_model() {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
    
    model *= glm::mat4_cast(p_orientation);

    model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

    return model;
}

void transform::set_rotation(const glm::quat& orientation) {
    p_orientation = glm::normalize(orientation);
}

void transform::rotate(float degrees, 
                       const utilz::vector3f& axis) {

    glm::vec3 rotation_axis = utils::vec3f_to_glm(axis);

    if (glm::dot(rotation_axis, rotation_axis) <= 0.0f)
        return;

    rotation_axis = glm::normalize(rotation_axis);

    glm::quat delta = glm::angleAxis(glm::radians(degrees), rotation_axis);

    p_orientation = glm::normalize(delta * p_orientation);
}

utilz::vector3f transform::forward() const {
    glm::vec3 direction = p_orientation * glm::vec3(0.0f, 0.0f, -1.0f);

    return utilz::vector3f(direction.x, direction.y, direction.z);
}

utilz::vector3f transform::right() const {
    glm::vec3 direction = p_orientation * glm::vec3(1.0f, 0.0f, 0.0f);

    return utilz::vector3f(direction.x, direction.y, direction.z);
}

utilz::vector3f transform::up() const {
    glm::vec3 direction = p_orientation * glm::vec3(0.0f, 1.0f, 0.0f);
    return utilz::vector3f(direction.x, direction.y, direction.z);
}

