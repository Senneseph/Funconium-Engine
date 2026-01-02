#include "demo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "asset_loader.h"
#include "timing.h"

// Function to register controls
ControlMapping* register_controls(ControlMapping* control_mappings, size_t count) {
    // Allocate memory for the registered controls
    ControlMapping* registered_controls = (ControlMapping*)malloc(count * sizeof(ControlMapping));
    if (registered_controls == NULL) {
        fprintf(stderr, "Failed to allocate memory for registered controls.\n");
        return NULL;
    }

    // Copy the control mappings
    for (size_t i = 0; i < count; i++) {
        registered_controls[i] = control_mappings[i];
    }

    return registered_controls;
}

// Global variables for FPS calculation
#include "timing.h"
static uint64_t last_fps_time = 0;
static int frame_count = 0;
static float current_fps = 0.0f;
static float current_frame_time = 0.0f;
static uint64_t last_frame_start = 0;

// Function to calculate FPS and frame time
void calculate_fps() {
    uint64_t current_time = get_current_time_ns();
    
    // Calculate frame time
    if (last_frame_start != 0) {
        uint64_t frame_time_ns = current_time - last_frame_start;
        current_frame_time = frame_time_ns / 1000000.0f; // Convert to milliseconds
    }
    last_frame_start = current_time;
    
    // Calculate FPS (update once per second)
    if (current_time - last_fps_time >= 1000000000) { // 1 second in nanoseconds
        current_fps = (float)frame_count / ((current_time - last_fps_time) / 1000000000.0f);
        frame_count = 0;
        last_fps_time = current_time;
    }
    frame_count++;
}

// Function to get current FPS
float get_current_fps() {
    return current_fps;
}

// Function to get current frame time
float get_current_frame_time() {
    return current_frame_time;
}

// Function to draw the screen
void draw_screen(void* scene_data) {
    (void)scene_data; // Suppress unused parameter warning
    // Placeholder for drawing the screen
    // Removed excessive console output
    calculate_fps();
}

// Function to play sound
void play_sound(Sound sound) {
    (void)sound; // Suppress unused parameter warning
    // Placeholder for playing sound
    // Removed excessive console output
}

// Function to initialize the engine
void* initialize_engine(void* engine_config) {
    (void)engine_config; // Suppress unused parameter warning
    // Placeholder for initializing the engine
    printf("Initializing the engine...\n");
    return (void*)1; // Return a non-NULL pointer to indicate success
}

// Function to shut down the engine
void shutdown_engine(void* engine_state) {
    (void)engine_state; // Suppress unused parameter warning
    // Placeholder for shutting down the engine
    printf("Shutting down the engine...\n");
}

// Function to detect hardware and prepare resources
bool detect_hardware_and_prepare(void* engine_config) {
    (void)engine_config; // Suppress unused parameter warning
    // Placeholder for hardware detection and resource preparation
    printf("Detecting hardware and preparing resources...\n");
    return true; // Return true to indicate success
}