#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "demo.h"
#include "asset_loader.h"
#include "demo_core.h"
#include "vulkan_wrapper.h"
#include "timing.h"
#include "logger.h"

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

    log_message("Starting the Funconium Engine Demo (Windows Vulkan)...");
    printf("Starting the Funconium Engine Demo (Windows Vulkan)...\n");

    // Initialize the engine
    void* engine_config = NULL; // Placeholder for engine configuration
    void* engine_state = initialize_engine(engine_config);
    if (engine_state == NULL) {
        fprintf(stderr, "Failed to initialize the engine.\n");
        return 1;
    }

    // Load assets
    printf("Loading assets...\n");
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

    // Detect hardware and prepare resources
    if (!detect_hardware_and_prepare(engine_config)) {
        fprintf(stderr, "Failed to detect hardware and prepare resources.\n");
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Configure the core engine for Vulkan
    CoreEngineConfig config = {
        .window_width = 800,
        .window_height = 600,
        .fullscreen = false,
        .vsync = true
    };

    // Initialize Vulkan
    VulkanState* vulkan_state = initialize_vulkan(&config);
    if (vulkan_state == NULL) {
        fprintf(stderr, "Failed to initialize Vulkan.\n");
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Main demo loop
    printf("Dragon Raiders Demo is running. Press ESC to quit.\n");

    // Main loop
    while (vulkan_state->running) {
        handle_vulkan_input_events(vulkan_state);
        update_game_state(vulkan_state);
        render_vulkan(vulkan_state);
        sleep_ms(16); // Use target frame time for ~60 FPS
    }

    // Clean up Vulkan
    shutdown_vulkan(vulkan_state);

    // Shutdown the engine
    shutdown_engine(engine_state);

    // Free the assets
    free_asset(dark_knight_asset);
    free_asset(pieta_asset);

    log_message("Demo shutdown complete.");
    printf("Demo shutdown complete.\n");

    // Shutdown the logger
    shutdown_logger();

    return 0;
}