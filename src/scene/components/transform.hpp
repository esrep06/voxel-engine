#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cpp-utilz/math/vector3.hpp>
#include <core/utils/utils.hpp>

class transform {
public: 
    transform(utilz::vector3f position, utilz::vector3f scale);
    transform();

    glm::mat4 get_model();
    utilz::vector3f forward() const;
    utilz::vector3f right() const;
    utilz::vector3f up() const;

    utilz::vector3f position = utilz::vector3f(0.0f);
    utilz::vector3f scale = utilz::vector3f(1.0f);

    void set_rotation(const glm::quat& orientation);
    void rotate(float degrees, const utilz::vector3f& axis);
private: 
    glm::quat p_orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    float p_rotation_deg = 0.0f;
};

