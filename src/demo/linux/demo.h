#ifndef DEMO_H
#define DEMO_H

#include <stddef.h>
#include <stdbool.h>

// Define the ControlMapping structure
typedef struct {
    int key;
    void (*callback)(void);
} ControlMapping;

// Define the Sound structure
typedef struct {
    void* data;
    size_t size;
    int channels;
    int sample_rate;
} Sound;

// Define the EngineConfig structure
typedef struct {
    bool defer_window_creation;
    bool use_fullscreen;
    bool use_exclusive_fullscreen;
    int window_width;
    int window_height;
    int font_size;
} EngineConfig;

// Function to register controls
ControlMapping* register_controls(ControlMapping* control_mappings, size_t count);

// Function to draw the screen
void draw_screen(void* scene_data);

// Function to play sound
void play_sound(Sound sound);

// Function to initialize the engine
void* initialize_engine(void* engine_config);

// Function to shut down the engine
void shutdown_engine(void* engine_state);

// Function to detect hardware and prepare resources
bool detect_hardware_and_prepare(void* engine_config);

#endif // DEMO_H