#ifndef VULKAN_WRAPPER_H
#define VULKAN_WRAPPER_H

#include <stdbool.h>
#include "demo_core.h"

// Vulkan state structure
typedef struct {
    void* instance;
    void* physical_device;
    void* device;
    void* surface;
    void* swapchain;
    void* render_pass;
    void* pipeline;
    void* command_pool;
    void* command_buffers;
    void* image_available_semaphores;
    void* render_finished_semaphores;
    void* in_flight_fences;
    int current_frame;
    int window_width;
    int window_height;
    bool running;
} VulkanState;

// Function to initialize Vulkan
VulkanState* initialize_vulkan(CoreEngineConfig* config);

// Function to shutdown Vulkan
void shutdown_vulkan(VulkanState* vulkan_state);

// Function to handle Vulkan input events
void handle_vulkan_input_events(VulkanState* vulkan_state);

// Function to render with Vulkan
void render_vulkan(VulkanState* vulkan_state);

// Function to create Vulkan window surface
bool create_vulkan_surface(VulkanState* vulkan_state, void* window);

#endif // VULKAN_WRAPPER_H