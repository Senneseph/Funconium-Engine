#ifndef DEMO_H
#define DEMO_H

#include <stddef.h>

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

#endif // DEMO_H