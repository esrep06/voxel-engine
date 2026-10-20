#include <core/gl_layer/gl_runtime.hpp> 

uint8_t gl_runtime::glfw_initialize() {
    if (p_glfw_initialized) {
        std::cerr << "GLFW Context already created for this object..." << std::endl;

        return 1;
    }

    utilz::logger::log("Initializing GLFW context...\n");
    
    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "Error initializing GL context: ";

        const char* description = nullptr;

        glfwGetError(&description);

        std::cout << description << std::endl;
 
        return 0;
    }

    utilz::logger::log("GLFW Version: " + std::string(glfwGetVersionString()) + std::string("\n"));

    utilz::logger::log("Platform:\n");

    switch (glfwGetPlatform()) {
        case GLFW_PLATFORM_WIN32: 
            std::cout << "  Windows" << std::endl;
            break;
        case GLFW_PLATFORM_COCOA: 
            std::cout << "  MacOS" << std::endl;
            break;
        default: 
            std::cout << "  Linux or other" << std::endl;
            break;
    }

    p_glfw_initialized = true;

    return 1;
}

void gl_runtime::gl_terminate() {
    if (!p_glfw_initialized) return; 

    utilz::logger::log("Terminating GL context...\n", utilz::logger::WARNING);

    p_glfw_initialized = false;

    glfwTerminate();
}

gl_runtime::~gl_runtime() {
    gl_terminate();
}

