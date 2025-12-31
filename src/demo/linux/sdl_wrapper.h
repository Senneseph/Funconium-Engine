#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "demo_core.h"

// Function to initialize SDL
void* initialize_sdl(CoreEngineConfig* config, EngineConfig* demo_config);

// Function to shutdown SDL
void shutdown_sdl(void* engine_state);

// Function to handle SDL input events
void handle_sdl_input_events(void* engine_state);

// Function to render using SDL
void render_sdl(void* engine_state);

#endif // SDL_WRAPPER_H