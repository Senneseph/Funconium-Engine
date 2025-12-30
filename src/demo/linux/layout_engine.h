#ifndef LAYOUT_ENGINE_H
#define LAYOUT_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Forward declaration of Widget
typedef struct Widget Widget;

// Layout Manager
typedef struct {
    int width;
    int height;
    Widget** widgets;
    int widget_count;
} LayoutManager;

// Widget
typedef struct Widget {
    int x;
    int y;
    int width;
    int height;
    void (*render)(Widget* widget, SDL_Renderer* renderer);
    void* data;
    void (*free_data)(void* data);
} Widget;

// Text Widget Data
typedef struct {
    char* text;
    SDL_Color color;
    int font_size;
    char* font_path;
} TextWidgetData;

// Button Widget Data
typedef struct {
    char* text;
    SDL_Color color;
    SDL_Color background_color;
    int font_size;
    char* font_path;
    void (*on_click)(void);
} ButtonWidgetData;

// Container Widget Data
typedef struct {
    Widget** children;
    int child_count;
} ContainerWidgetData;

// Function to create a layout manager
LayoutManager* create_layout_manager(int width, int height);

// Function to add a widget to the layout manager
void add_widget_to_layout(LayoutManager* layout, Widget* widget);

// Function to render the layout
void render_layout(LayoutManager* layout, SDL_Renderer* renderer);

// Function to free the layout manager
void free_layout_manager(LayoutManager* layout);

// Function to create a text widget
Widget* create_text_widget(const char* text, SDL_Color color, int font_size, const char* font_path);

// Function to create a button widget
Widget* create_button_widget(const char* text, SDL_Color color, SDL_Color background_color, int font_size, const char* font_path, void (*on_click)(void));

// Function to create a container widget
Widget* create_container_widget();

// Function to add a child widget to a container widget
void add_child_to_container(Widget* container, Widget* child);

// Function to free a widget
void free_widget(Widget* widget);

#endif // LAYOUT_ENGINE_H