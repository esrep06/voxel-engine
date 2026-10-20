#pragma once 

#include <core/window/window.hpp> 
#include <core/input/input.hpp>
#include <core/time/time.hpp>
#include <render/renderer/renderer.hpp>
#include <render/camera/camera.hpp>

class application {
public:
    application(std::string title, uint16_t width, uint16_t height, utilz::rgba_color color);
    ~application();

    camera main_camera;
    
    void run();
    void render();

    class time get_time() const;
private:
    gl_runtime p_runtime; 
    window p_window;

    renderer p_renderer;
    class time p_time;

    uint8_t p_running = 1;
};

