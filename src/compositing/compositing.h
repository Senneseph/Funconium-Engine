#ifndef COMPOSITING_H
#define COMPOSITING_H

#include <stddef.h>

// Function to blend layers from temporary buffers
void* blend_layers(void* temporary_buffers, void* blending_parameters);

// Function to apply effects to the blended layers
void* apply_effects(void* blended_layers, void* effects);

#endif // COMPOSITING_H