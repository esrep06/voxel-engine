#include <core/utils/utils.hpp>

glm::vec3 utils::vec3f_to_glm(utilz::vector3f vec) {
    return glm::vec3(vec.x, vec.y, vec.z);
}
