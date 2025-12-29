#ifndef EARLY_RENDERING_H
#define EARLY_RENDERING_H

#include <stddef.h>

// Define the Entity structure
typedef struct {
    float x, y, z;
    float rotation;
    void* properties;
} Entity;

// Define the TemporaryBuffer structure
typedef struct {
    void* data;
    size_t size;
} TemporaryBuffer;

// Function to update an entity's state for the next frame
Entity update_entity(Entity entity, void* next_frame_state);

// Function to render an entity into a temporary buffer
TemporaryBuffer render_entity(Entity entity);

// Function to composite the final frame from temporary buffers
void* composite_frame(TemporaryBuffer* buffers, size_t buffer_count);

#endif // EARLY_RENDERING_H