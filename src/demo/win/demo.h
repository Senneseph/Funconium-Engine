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

// Define the FPS display position enum
typedef enum {
    FPS_POSITION_TOP_LEFT,
    FPS_POSITION_TOP_RIGHT,
    FPS_POSITION_BOTTOM_LEFT,
    FPS_POSITION_BOTTOM_RIGHT
} FPSPosition;

// Define the EngineConfig structure
typedef struct {
    bool defer_window_creation;
    bool use_fullscreen;
    bool use_exclusive_fullscreen;
    int window_width;
    int window_height;
    int font_size;
    bool show_fps;
    bool show_frame_time;
    FPSPosition fps_position;
    char* fps_font_path;
} EngineConfig;

// Function to register controls
ControlMapping* register_controls(ControlMapping* control_mappings, size_t count);

// Function to draw the screen
void draw_screen(void* scene_data);

// Function to play sound
void play_sound(Sound sound);

// Function to get current FPS
float get_current_fps();

// Function to get current frame time
float get_current_frame_time();

// Function to initialize the engine
void* initialize_engine(void* engine_config);

// Function to shut down the engine
void shutdown_engine(void* engine_state);

// Function to detect hardware and prepare resources
bool detect_hardware_and_prepare(void* engine_config);

#endif // DEMO_H