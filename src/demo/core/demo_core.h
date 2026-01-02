#ifndef DEMO_CORE_H
#define DEMO_CORE_H

#include <stdbool.h>

// Platform-specific includes
#if defined(_WIN32)
#include "../win/demo.h"
#elif defined(__linux__)
#include "../linux/demo.h"
#elif defined(__EMSCRIPTEN__)
#include "../wasm/demo.h"
#else
#include "../linux/demo.h" // Default to Linux
#endif

// Structure to hold core engine configuration
typedef struct {
    int window_width;
    int window_height;
    bool fullscreen;
    bool vsync;
} CoreEngineConfig;

// Structure to hold game state
typedef struct {
    void* renderer;
    void* window;
    bool running;
    EngineConfig demo_config;
} GameState;

// Function to initialize the core engine
void* initialize_core_engine(CoreEngineConfig* config);

// Function to shutdown the core engine
void shutdown_core_engine(void* engine_state);

// Function to handle input events
void handle_input_events(void* engine_state);

// Function to update the game state
void update_game_state(void* engine_state);

// Function to render the game
void render_game(void* engine_state);

#endif // DEMO_CORE_H