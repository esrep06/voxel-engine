cmake_minimum_required(VERSION 3.20)

project(VoxelEngine 
    VERSION 0.1.0
    LANGUAGES CXX
)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ClangD compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(VoxelEngine ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(VoxelEngine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glew/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/cpp-utilz/include"
)

# GLFW
add_subdirectory(include/glfw)

# GLEW
add_subdirectory(include/glew/build/cmake)

# GLM
add_subdirectory(include/glm)

# Libraries
target_link_libraries(VoxelEngine PRIVATE
    glfw
    glew_s
    glm::glm
    OpenGL::GL
    Freetype::Freetype
)

if(APPLE)
    target_link_libraries(Engine PRIVATE
        "-framework OpenGL"
        "-framework CoreVideo"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework QuartzCore"
)
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(VoxelEngine PRIVATE /W4)
else()
    target_compile_options(VoxelEngine PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

