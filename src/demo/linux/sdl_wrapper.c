#include "sdl_wrapper.h"
#include "layout_engine.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef USE_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

// Function to initialize SDL
void* initialize_sdl(CoreEngineConfig* config) {
    #ifdef USE_SDL
    printf("Initializing SDL...\n");
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return NULL;
    }
    printf("SDL initialized successfully.\n");

    // Initialize SDL_image
    printf("Initializing SDL_image...\n");
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return NULL;
    }
    printf("SDL_image initialized successfully.\n");

    // Initialize SDL_ttf
    printf("Initializing SDL_ttf...\n");
    if (TTF_Init() == -1) {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }
    printf("SDL_ttf initialized successfully.\n");

    // Create a window
    printf("Creating window...\n");
    Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    if (config->fullscreen) {
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    SDL_Window* window = SDL_CreateWindow("Dragon Raiders Demo",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            config->window_width,
                                            config->window_height,
                                            window_flags);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }
    printf("Window created successfully.\n");

    // Create a renderer
    printf("Creating renderer...\n");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }
    printf("Renderer created successfully.\n");

    // Set VSYNC
    if (config->vsync) {
        printf("Setting VSYNC...\n");
        SDL_RenderSetVSync(renderer, 1);
        printf("VSYNC set successfully.\n");
    }

    // Allocate game state
    printf("Allocating game state...\n");
    GameState* game_state = (GameState*)malloc(sizeof(GameState));
    if (game_state == NULL) {
        fprintf(stderr, "Failed to allocate memory for game state.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return NULL;
    }
    printf("Game state allocated successfully.\n");

    game_state->renderer = renderer;
    game_state->window = window;
    game_state->running = true;

    printf("SDL initialized successfully.\n");
    return game_state;
    #else
    printf("USE_SDL is not defined.\n");
    return NULL;
    #endif
}

// Function to shutdown SDL
void shutdown_sdl(void* engine_state) {
    #ifdef USE_SDL
    if (engine_state != NULL) {
        GameState* state = (GameState*)engine_state;
        SDL_DestroyRenderer((SDL_Renderer*)state->renderer);
        SDL_DestroyWindow((SDL_Window*)state->window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        free(state);
    }
    #endif
}

// Function to handle SDL input events
void handle_sdl_input_events(void* engine_state) {
    #ifdef USE_SDL
    GameState* state = (GameState*)engine_state;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state->running = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                state->running = false;
            }
        }
    }
    #endif
}

// Function to render using SDL
void render_sdl(void* engine_state) {
    #ifdef USE_SDL
    GameState* state = (GameState*)engine_state;
    SDL_Renderer* renderer = (SDL_Renderer*)state->renderer;

    // Get the window dimensions
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Create a layout manager
    LayoutManager* layout = create_layout_manager(window_width, window_height);
    if (layout == NULL) {
        fprintf(stderr, "Failed to create layout manager\n");
        SDL_RenderPresent(renderer);
        return;
    }

    // Create a text widget for the message
    Widget* message_widget = create_text_widget(
        "Dragon Raiders, powered by the Funconium Engine",
        (SDL_Color){255, 255, 255, 255},
        36,
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    );
    if (message_widget == NULL) {
        fprintf(stderr, "Failed to create text widget\n");
        free_layout_manager(layout);
        SDL_RenderPresent(renderer);
        return;
    }

    // Center the text widget
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 36);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 36);
    }
    if (font != NULL) {
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Dragon Raiders, powered by the Funconium Engine", (SDL_Color){255, 255, 255, 255});
        if (textSurface != NULL) {
            message_widget->width = textSurface->w;
            message_widget->height = textSurface->h;
            message_widget->x = (window_width - textSurface->w) / 2;
            message_widget->y = (window_height - textSurface->h) / 2;
            SDL_FreeSurface(textSurface);
        }
        TTF_CloseFont(font);
    }

    // Add the widget to the layout manager
    add_widget_to_layout(layout, message_widget);

    // Render the layout
    render_layout(layout, renderer);

    // Free the layout manager
    free_layout_manager(layout);

    // Present the renderer
    SDL_RenderPresent(renderer);
    #endif
}