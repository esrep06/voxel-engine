#include <core/time/time.hpp>

time::time()
: p_start(std::chrono::steady_clock::now()), p_last_frame(p_start)
{}

void time::update() {
    auto current = std::chrono::steady_clock::now();

    p_delta_time = std::chrono::duration<float>(
        current - p_last_frame
    ).count();

    p_elapsed_time = std::chrono::duration<double>(
        current - p_start 
    ).count(); 

    p_last_frame = current;
}   

float time::fps() const {
    if (p_delta_time <= 0.0f) 
        return 0.0f; 

    return 1.0f / p_delta_time;
}

float time::delta_time() const { return p_delta_time; }
float time::elapsed_time() const { return p_elapsed_time; }


