#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "demo.h"
#include "asset_loader.h"

// Callback function for quitting the demo
void quit_demo() {
    printf("Quitting the demo...\n");
    exit(0);
}

int main() {
    printf("Starting the Funconium Engine Demo...\n");

    // Initialize the engine
    void* engine_config = NULL; // Placeholder for engine configuration
    void* engine_state = initialize_engine(engine_config);
    if (engine_state == NULL) {
        fprintf(stderr, "Failed to initialize the engine.\n");
        return 1;
    }

    // Load assets
    Asset dark_knight_asset = load_asset("resources/models/dark-knight-spiked-black-armored-warrior.zip");
    Asset pieta_asset = load_asset("resources/models/pieta-cinematic-wings.zip");

    if (dark_knight_asset.data == NULL || pieta_asset.data == NULL) {
        fprintf(stderr, "Failed to load assets.\n");
        shutdown_engine(engine_state);
        return 1;
    }

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

    // Main demo loop
    printf("Dragon Raiders Demo is running. Press ESC to quit.\n");

    // Main loop flag
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

    // Shutdown the engine
    shutdown_engine(engine_state);

    // Free the assets
    free_asset(dark_knight_asset);
    free_asset(pieta_asset);

    return 0;
}