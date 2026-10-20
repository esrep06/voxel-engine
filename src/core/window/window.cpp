#include <core/window/window.hpp>

window::window(std::string title, uint16_t width, uint16_t height, utilz::rgba_color color) 
    : p_title(title), p_width(width), p_height(height), p_color(color)
{}

uint8_t window::create() {
    if (p_window_initialized) {
        return 0;
    }

    utilz::logger::log("Creating GLFW window...\n");

    // Request OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    p_window = glfwCreateWindow(p_width, p_height, p_title.c_str(), NULL, NULL);

    if (!p_window)
    {
        std::cerr << "Error creating GLFW window..." << std::endl;

        return 0;
    }

    glfwMakeContextCurrent(p_window);

    set_callbacks();

    if (!glew_create()) {
        glfwMakeContextCurrent(nullptr);
        glfwDestroyWindow(p_window);
        p_window = nullptr;
        return 0;
    }

    glfwSwapInterval(1);

    glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    p_window_initialized = true;

    return 1;
}


uint8_t window::glew_create() {
    if (p_glew_initialized) {
        std::cerr << "GLEW Context already assigned for this object..." << std::endl;

        return 0;
    }

    if (!glfwGetCurrentContext()) {
        std::cerr << "No current OpenGL context\n"; 

        return 0;
    }

    glewExperimental = GL_TRUE;

    utilz::logger::log("Creating GLEW context...\n");
    
    GLenum err = glewInit();

    if (GLEW_OK != err) {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;

        return 0;
    }
    
    utilz::logger::log("Using GLEW: "); std::cout << glewGetString(GLEW_VERSION) << std::endl;

    utilz::logger::log("GPU Information:\n");   

    // Query graphics card information
    const GLubyte* vendor   = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER); // Usually contains GPU model name
    const GLubyte* version  = glGetString(GL_VERSION);

    std::cout << "  Vendor:   " << vendor << std::endl;
    std::cout << "  Renderer: " << renderer << std::endl;
    std::cout << "  Version:  " << version << std::endl;

    p_glew_initialized = true;

    return 1;
}

GLFWwindow* window::get_window() const { 
    return p_window;
}

uint8_t window::should_close() {
    return glfwWindowShouldClose(p_window);
}

void window::clearColor() {
    glClearColor(RGBA_NORMALIZED_FLOAT(p_color));
}

void window::set_callbacks() {
    glfwSetKeyCallback(p_window, input::key_callback);
    glfwSetCharCallback(p_window, input::text_stream_callback);
    glfwSetCursorPosCallback(p_window, input::mouse_position_callback);
    glfwSetMouseButtonCallback(p_window, input::mouse_button_callback);
}

window::~window() {
    if (!p_window) return; 

    utilz::logger::log("Terminating window...\n", utilz::logger::WARNING);

    glfwDestroyWindow(p_window);
}

