#include <core/application/application.hpp>

application::application(std::string title, uint16_t width, uint16_t height, utilz::rgba_color color)
    : main_camera(utilz::vector3f(0.0f, 0.0f, 3.0f), 90.0f), p_window(title, width, height, color) 
{    
    utilz::logger::log("Creating application...\n");

    if (!p_runtime.glfw_initialize()) {
        throw std::runtime_error("Application failed on runtime initialization...");
    }

    if (!p_window.create()) {
        throw std::runtime_error("Application failed on window creation...");
    }
}

void application::run() {
    p_running = 1;

    if (!p_renderer.init()) {
        throw std::runtime_error("Renderer failed to initialize!");
    }

    utilz::vector3f up = utilz::vector3f(0.0f, 1.0f, 0.0f);
    const float camera_speed = 10.0f;

    utilz::vector3f a = utilz::vector3f(3, 0, 2);
    utilz::vector3f b = utilz::vector3f(-1, 4, 2);
    utilz::vector3f direction;

    float yaw = -90; 
    float pitch = 0;
    const float sens = 0.3f;

    while (!p_window.should_close())
    {
        p_time.update();

        glfwPollEvents();

        p_window.clearColor();

        utilz::vector2f mouse_movement = input::get_mouse_delta() * sens;

        yaw += mouse_movement.x * sens;
        pitch -= mouse_movement.y * sens;

        pitch = utilz::m_utilz::clampf(-89.0f, 89.0f, pitch);

        glm::quat yaw_rotation = glm::angleAxis(glm::radians(-(yaw + 90.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::quat pitch_rotation = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::quat orientation = glm::normalize(yaw_rotation * pitch_rotation);

        main_camera.transform.set_rotation(orientation);

        if (input::get_key(GLFW_KEY_W)) { 
            main_camera.transform.position += main_camera.transform.forward() * camera_speed * get_time().delta_time();
        }

        if (input::get_key(GLFW_KEY_S)) {
            main_camera.transform.position -= main_camera.transform.forward() * camera_speed * get_time().delta_time();
        }

        if (input::get_key(GLFW_KEY_D)) {
            main_camera.transform.position += utilz::vector3f::normalize(utilz::vector3f::cross(main_camera.transform.forward(), up)) * camera_speed * get_time().delta_time();
        }

        if (input::get_key(GLFW_KEY_A)) {
            main_camera.transform.position -= utilz::vector3f::normalize(utilz::vector3f::cross(main_camera.transform.forward(), up)) * camera_speed * get_time().delta_time();
        }

        if (input::get_key(GLFW_KEY_SPACE)) {
            main_camera.transform.position += utilz::vector3f(0.0, 1.0f, 0.0f) * camera_speed * get_time().delta_time();
        }

        if (input::get_key(GLFW_KEY_LEFT_CONTROL)) {
            main_camera.transform.position -= utilz::vector3f(0.0, 1.0f, 0.0f) * camera_speed * get_time().delta_time();
        }

        p_renderer.render(main_camera);

        glfwSwapBuffers(p_window.get_window());

        input::end_frame();
    }
}

void application::render() {
    p_window.clearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

class time application::get_time() const { return p_time; }

application::~application() { }

