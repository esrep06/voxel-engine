#pragma once 

#include <chrono>

class time {
public: 
    time();

    void update();

    float delta_time() const;
    float elapsed_time() const;
    
    float fps() const;

private: 
    std::chrono::steady_clock::time_point p_start;
    std::chrono::steady_clock::time_point p_last_frame;

    float p_delta_time = 0.0f; 
    float p_elapsed_time = 0.0f;
};

