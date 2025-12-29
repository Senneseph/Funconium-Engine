#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stddef.h>

// Function to schedule a frame based on the desired FPS
float schedule_frame(float desired_fps, float current_time);

// Function to scale the workload based on available compute power
void* scale_workload(void* available_compute_power, void* workload);

// Function to set the maximum settings for the given FPS
void* set_max_settings(float desired_fps);

#endif // SCHEDULER_H