#include <core/application/application.hpp>
#include <cpp-utilz/color/color.hpp>

int main(void)
{
    application app = application("Voxel Engine", 1600, 900, utilz::rgba_color{100, 100, 100, 255});

    app.run();

    return 0;
}


