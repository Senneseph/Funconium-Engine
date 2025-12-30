#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "demo.h"
#include "asset_loader.h"
#include "demo_core.h"
#include "sdl_wrapper.h"
#include "logger.h"

#ifdef USE_SDL
#include <SDL2/SDL.h>
#endif

// Callback function for quitting the demo
void quit_demo() {
    printf("Quitting the demo...\n");
    exit(0);
}

int main() {
    // Initialize the logger
    LoggerConfig logger_config = {
        .log_file_path = "demo.log",
        .max_log_size = 1024 * 1024 // 1MB
    };
    if (!initialize_logger(&logger_config)) {
        fprintf(stderr, "Failed to initialize logger.\n");
        return 1;
    }

    log_message("Starting the Funconium Engine Demo...");
    printf("Starting the Funconium Engine Demo...\n");

    // Initialize the engine
    void* engine_config = NULL; // Placeholder for engine configuration
    void* engine_state = initialize_engine(engine_config);
    if (engine_state == NULL) {
        fprintf(stderr, "Failed to initialize the engine.\n");
        return 1;
    }

    // Load assets
    log_message("Loading assets...");
    Asset dark_knight_asset = load_asset("resources/models/dark-knight-spiked-black-armored-warrior.zip");
    Asset pieta_asset = load_asset("resources/models/pieta-cinematic-wings.zip");

    if (dark_knight_asset.data == NULL || pieta_asset.data == NULL) {
        log_message("Failed to load assets.");
        fprintf(stderr, "Failed to load assets.\n");
        shutdown_engine(engine_state);
        return 1;
    }

    log_message("Assets loaded successfully.");
    printf("Assets loaded successfully.\n");

    // Register controls
    ControlMapping control_mappings[] = {
        {0x1B, quit_demo} // ESC key to quit
    };
    size_t control_count = sizeof(control_mappings) / sizeof(ControlMapping);
    ControlMapping* registered_controls = register_controls(control_mappings, control_count);
    if (registered_controls == NULL) {
        fprintf(stderr, "Failed to register controls.\n");
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Detect hardware and prepare resources
    if (!detect_hardware_and_prepare(engine_config)) {
        fprintf(stderr, "Failed to detect hardware and prepare resources.\n");
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Main demo loop
    printf("Dragon Raiders Demo is running. Press ESC to quit.\n");

    #ifdef USE_SDL
    // Configure the engine
    CoreEngineConfig config = {
        .window_width = 800,
        .window_height = 600,
        .fullscreen = false,
        .vsync = true
    };

    // Initialize the core engine
    void* core_engine_state = initialize_core_engine(&config);
    if (core_engine_state == NULL) {
        fprintf(stderr, "Failed to initialize the core engine.\n");
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Initialize SDL
    void* sdl_state = initialize_sdl(&config);
    if (sdl_state == NULL) {
        fprintf(stderr, "Failed to initialize SDL.\n");
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_core_engine(core_engine_state);
        shutdown_engine(engine_state);
        return 1;
    }

    // Main loop
    while (((GameState*)sdl_state)->running) {
        handle_sdl_input_events(sdl_state);
        update_game_state(core_engine_state);
        render_sdl(sdl_state);
        SDL_Delay(16); // 16ms for ~60 FPS
    }

    // Clean up SDL
    shutdown_sdl(sdl_state);
    // Clean up the core engine
    shutdown_core_engine(core_engine_state);
    #else
    // Fallback to console output if SDL is not available
    bool running = true;
    while (running) {
        // Draw the screen
        void* scene_data = NULL; // Placeholder for scene data
        draw_screen(scene_data);

        // Play sound
        Sound sound = {NULL, 0, 0, 0}; // Placeholder for sound
        play_sound(sound);

        // Simulate a frame delay
        #ifdef _WIN32
        Sleep(16); // 16ms for ~60 FPS
        #else
        usleep(16000); // 16ms for ~60 FPS
        #endif
    }
    #endif

    // Shutdown the engine
    shutdown_engine(engine_state);

    // Free the assets
    free_asset(dark_knight_asset);
    free_asset(pieta_asset);

    // Shutdown the logger
    shutdown_logger();

    log_message("Demo shutdown complete.");
    printf("Demo shutdown complete.\n");

    return 0;
}