#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "demo.h"
#include "asset_loader.h"

#ifdef USE_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

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

    #ifdef USE_SDL
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Dragon Raiders Demo",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           800, 600,
                                           SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        free_asset(dark_knight_asset);
        free_asset(pieta_asset);
        shutdown_engine(engine_state);
        return 1;
    }

    // Load a placeholder image for rendering
    // Note: The ZIP file contains a model, not an image. For now, we'll skip image loading.
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

    // Load a font and render text
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 24);
    }
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    } else {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Dragon Raiders, powered by the Funconium Engine", textColor);
        if (textSurface == NULL) {
            fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            if (texture == NULL) {
                fprintf(stderr, "Failed to create texture from text: %s\n", SDL_GetError());
            }
        }
        TTF_CloseFont(font);
    }

    // Main loop flag
    bool running = true;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the loaded texture (if available)
        if (texture != NULL) {
            SDL_Rect dest_rect = {300, 200, 200, 200};
            SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Simulate a frame delay
        SDL_Delay(16); // 16ms for ~60 FPS
    }

    // Clean up SDL
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
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

    return 0;
}