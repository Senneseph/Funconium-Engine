#include "layout_engine.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function to create a layout manager
LayoutManager* create_layout_manager(int width, int height) {
    LayoutManager* layout = (LayoutManager*)malloc(sizeof(LayoutManager));
    if (layout == NULL) {
        return NULL;
    }
    layout->width = width;
    layout->height = height;
    layout->widgets = NULL;
    layout->widget_count = 0;
    return layout;
}

// Function to add a widget to the layout manager
void add_widget_to_layout(LayoutManager* layout, Widget* widget) {
    if (layout == NULL || widget == NULL) {
        return;
    }
    layout->widget_count++;
    layout->widgets = (Widget**)realloc(layout->widgets, layout->widget_count * sizeof(Widget*));
    if (layout->widgets == NULL) {
        layout->widget_count = 0;
        return;
    }
    layout->widgets[layout->widget_count - 1] = widget;
}

// Function to render the layout
void render_layout(LayoutManager* layout, SDL_Renderer* renderer) {
    if (layout == NULL || renderer == NULL) {
        return;
    }
    for (int i = 0; i < layout->widget_count; i++) {
        Widget* widget = layout->widgets[i];
        if (widget != NULL && widget->render != NULL) {
            widget->render(widget, renderer);
        }
    }
}

// Function to free the layout manager
void free_layout_manager(LayoutManager* layout) {
    if (layout == NULL) {
        return;
    }
    for (int i = 0; i < layout->widget_count; i++) {
        if (layout->widgets[i] != NULL) {
            free_widget(layout->widgets[i]);
        }
    }
    free(layout->widgets);
    free(layout);
}

// Function to render a text widget
void render_text_widget(Widget* widget, SDL_Renderer* renderer) {
    if (widget == NULL || renderer == NULL || widget->data == NULL) {
        return;
    }
    TextWidgetData* data = (TextWidgetData*)widget->data;
    TTF_Font* font = TTF_OpenFont(data->font_path, data->font_size);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }
    
    // Render outline if enabled
    if (data->has_outline) {
        // Render outline by drawing the text multiple times with offset
        for (int dx = -data->outline_thickness; dx <= data->outline_thickness; dx++) {
            for (int dy = -data->outline_thickness; dy <= data->outline_thickness; dy++) {
                if (dx == 0 && dy == 0) continue; // Skip the center (main text)
                
                SDL_Surface* outlineSurface = TTF_RenderText_Blended(font, data->text, data->outline_color);
                if (outlineSurface != NULL) {
                    SDL_Texture* outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
                    if (outlineTexture != NULL) {
                        SDL_Rect outline_rect = {widget->x + dx, widget->y + dy, outlineSurface->w, outlineSurface->h};
                        SDL_RenderCopy(renderer, outlineTexture, NULL, &outline_rect);
                        SDL_DestroyTexture(outlineTexture);
                    }
                    SDL_FreeSurface(outlineSurface);
                }
            }
        }
    }
    
    // Render main text
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, data->text, data->color);
    if (textSurface == NULL) {
        fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (texture == NULL) {
        fprintf(stderr, "Failed to create texture from text: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect dest_rect = {widget->x, widget->y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

// Function to free text widget data
void free_text_widget_data(void* data) {
    if (data == NULL) {
        return;
    }
    TextWidgetData* textData = (TextWidgetData*)data;
    free(textData->text);
    free(textData->font_path);
    free(textData);
}

// Function to create a text widget
Widget* create_text_widget(const char* text, SDL_Color color, int font_size, const char* font_path) {
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (widget == NULL) {
        return NULL;
    }
    TextWidgetData* data = (TextWidgetData*)malloc(sizeof(TextWidgetData));
    if (data == NULL) {
        free(widget);
        return NULL;
    }
    data->text = (char*)malloc(strlen(text) + 1);
    if (data->text == NULL) {
        free(data);
        free(widget);
        return NULL;
    }
    strcpy(data->text, text);
    data->color = color;
    data->outline_color = (SDL_Color){0, 0, 0, 255}; // Default black outline
    data->font_size = font_size;
    data->font_path = (char*)malloc(strlen(font_path) + 1);
    if (data->font_path == NULL) {
        free(data->text);
        free(data);
        free(widget);
        return NULL;
    }
    strcpy(data->font_path, font_path);
    data->has_outline = false;
    data->outline_thickness = 1;
    widget->x = 0;
    widget->y = 0;
    widget->width = 0;
    widget->height = 0;
    widget->render = render_text_widget;
    widget->data = data;
    widget->free_data = free_text_widget_data;
    return widget;
}

// Function to create a text widget with outline
Widget* create_text_widget_with_outline(const char* text, SDL_Color color, SDL_Color outline_color, int font_size, const char* font_path, int outline_thickness) {
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (widget == NULL) {
        return NULL;
    }
    TextWidgetData* data = (TextWidgetData*)malloc(sizeof(TextWidgetData));
    if (data == NULL) {
        free(widget);
        return NULL;
    }
    data->text = (char*)malloc(strlen(text) + 1);
    if (data->text == NULL) {
        free(data);
        free(widget);
        return NULL;
    }
    strcpy(data->text, text);
    data->color = color;
    data->outline_color = outline_color;
    data->font_size = font_size;
    data->font_path = (char*)malloc(strlen(font_path) + 1);
    if (data->font_path == NULL) {
        free(data->text);
        free(data);
        free(widget);
        return NULL;
    }
    strcpy(data->font_path, font_path);
    data->has_outline = true;
    data->outline_thickness = outline_thickness;
    widget->x = 0;
    widget->y = 0;
    widget->width = 0;
    widget->height = 0;
    widget->render = render_text_widget;
    widget->data = data;
    widget->free_data = free_text_widget_data;
    return widget;
}

// Function to render a button widget
void render_button_widget(Widget* widget, SDL_Renderer* renderer) {
    if (widget == NULL || renderer == NULL || widget->data == NULL) {
        return;
    }
    ButtonWidgetData* data = (ButtonWidgetData*)widget->data;
    // Draw background
    SDL_SetRenderDrawColor(renderer, data->background_color.r, data->background_color.g, data->background_color.b, data->background_color.a);
    SDL_Rect background_rect = {widget->x, widget->y, widget->width, widget->height};
    SDL_RenderFillRect(renderer, &background_rect);
    // Draw text
    TTF_Font* font = TTF_OpenFont(data->font_path, data->font_size);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, data->text, data->color);
    if (textSurface == NULL) {
        fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (texture == NULL) {
        fprintf(stderr, "Failed to create texture from text: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect dest_rect = {widget->x + (widget->width - textWidth) / 2, widget->y + (widget->height - textHeight) / 2, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

// Function to free button widget data
void free_button_widget_data(void* data) {
    if (data == NULL) {
        return;
    }
    ButtonWidgetData* buttonData = (ButtonWidgetData*)data;
    free(buttonData->text);
    free(buttonData->font_path);
    free(buttonData);
}

// Function to create a button widget
Widget* create_button_widget(const char* text, SDL_Color color, SDL_Color background_color, int font_size, const char* font_path, void (*on_click)(void)) {
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (widget == NULL) {
        return NULL;
    }
    ButtonWidgetData* data = (ButtonWidgetData*)malloc(sizeof(ButtonWidgetData));
    if (data == NULL) {
        free(widget);
        return NULL;
    }
    data->text = (char*)malloc(strlen(text) + 1);
    if (data->text == NULL) {
        free(data);
        free(widget);
        return NULL;
    }
    strcpy(data->text, text);
    data->color = color;
    data->background_color = background_color;
    data->font_size = font_size;
    data->font_path = (char*)malloc(strlen(font_path) + 1);
    if (data->font_path == NULL) {
        free(data->text);
        free(data);
        free(widget);
        return NULL;
    }
    strcpy(data->font_path, font_path);
    data->on_click = on_click;
    widget->x = 0;
    widget->y = 0;
    widget->width = 200;
    widget->height = 50;
    widget->render = render_button_widget;
    widget->data = data;
    widget->free_data = free_button_widget_data;
    return widget;
}

// Function to render a container widget
void render_container_widget(Widget* widget, SDL_Renderer* renderer) {
    if (widget == NULL || renderer == NULL || widget->data == NULL) {
        return;
    }
    ContainerWidgetData* data = (ContainerWidgetData*)widget->data;
    for (int i = 0; i < data->child_count; i++) {
        Widget* child = data->children[i];
        if (child != NULL && child->render != NULL) {
            child->render(child, renderer);
        }
    }
}

// Function to free container widget data
void free_container_widget_data(void* data) {
    if (data == NULL) {
        return;
    }
    ContainerWidgetData* containerData = (ContainerWidgetData*)data;
    for (int i = 0; i < containerData->child_count; i++) {
        if (containerData->children[i] != NULL) {
            free_widget(containerData->children[i]);
        }
    }
    free(containerData->children);
    free(containerData);
}

// Function to create a container widget
Widget* create_container_widget() {
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (widget == NULL) {
        return NULL;
    }
    ContainerWidgetData* data = (ContainerWidgetData*)malloc(sizeof(ContainerWidgetData));
    if (data == NULL) {
        free(widget);
        return NULL;
    }
    data->children = NULL;
    data->child_count = 0;
    widget->x = 0;
    widget->y = 0;
    widget->width = 0;
    widget->height = 0;
    widget->render = render_container_widget;
    widget->data = data;
    widget->free_data = free_container_widget_data;
    return widget;
}

// Function to add a child widget to a container widget
void add_child_to_container(Widget* container, Widget* child) {
    if (container == NULL || child == NULL || container->data == NULL) {
        return;
    }
    ContainerWidgetData* data = (ContainerWidgetData*)container->data;
    data->child_count++;
    data->children = (Widget**)realloc(data->children, data->child_count * sizeof(Widget*));
    if (data->children == NULL) {
        data->child_count = 0;
        return;
    }
    data->children[data->child_count - 1] = child;
}

// Function to free a widget
void free_widget(Widget* widget) {
    if (widget == NULL) {
        return;
    }
    if (widget->free_data != NULL) {
        widget->free_data(widget->data);
    }
    free(widget);
}