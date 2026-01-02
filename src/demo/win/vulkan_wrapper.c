#include "vulkan_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Global window handle
HWND global_hwnd = NULL;

// Function to initialize Vulkan
VulkanState* initialize_vulkan(CoreEngineConfig* config) {
    printf("Initializing Vulkan...\n");
    
    if (config == NULL) {
        fprintf(stderr, "Config is NULL.\n");
        return NULL;
    }
    
    // Allocate Vulkan state
    VulkanState* vulkan_state = (VulkanState*)malloc(sizeof(VulkanState));
    if (vulkan_state == NULL) {
        fprintf(stderr, "Failed to allocate memory for Vulkan state.\n");
        return NULL;
    }
    
    // Initialize Vulkan state
    memset(vulkan_state, 0, sizeof(VulkanState));
    vulkan_state->window_width = config->window_width;
    vulkan_state->window_height = config->window_height;
    vulkan_state->running = true;
    
    // Register window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "FunconiumVulkanWindow";
    
    if (!RegisterClass(&wc)) {
        fprintf(stderr, "Failed to register window class.\n");
        free(vulkan_state);
        return NULL;
    }
    
    // Create window
    DWORD window_style = WS_OVERLAPPEDWINDOW;
    RECT window_rect = {0, 0, config->window_width, config->window_height};
    AdjustWindowRect(&window_rect, window_style, FALSE);
    
    global_hwnd = CreateWindow(
        "FunconiumVulkanWindow",
        "Dragon Raiders Demo",
        window_style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        window_rect.right - window_rect.left,
        window_rect.bottom - window_rect.top,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );
    
    if (!global_hwnd) {
        fprintf(stderr, "Failed to create window.\n");
        free(vulkan_state);
        return NULL;
    }
    
    // Show window
    ShowWindow(global_hwnd, SW_SHOW);
    
    // Create Vulkan instance
    VkApplicationInfo app_info = {0};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Dragon Raiders Demo";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Funconium Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;
    
    VkInstanceCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    
    // Enable validation layers in debug builds
    const char* validation_layers[] = {"VK_LAYER_KHRONOS_validation"};
    uint32_t layer_count = 1;
    create_info.enabledLayerCount = layer_count;
    create_info.ppEnabledLayerNames = validation_layers;
    
    // Enable surface extension
    const char* extensions[] = {VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME};
    create_info.enabledExtensionCount = 2;
    create_info.ppEnabledExtensionNames = extensions;
    
    VkInstance instance;
    if (vkCreateInstance(&create_info, NULL, &instance) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create Vulkan instance.\n");
        DestroyWindow(global_hwnd);
        free(vulkan_state);
        return NULL;
    }
    vulkan_state->instance = instance;
    
    // Create surface
    VkWin32SurfaceCreateInfoKHR surface_create_info = {0};
    surface_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surface_create_info.hwnd = global_hwnd;
    surface_create_info.hinstance = GetModuleHandle(NULL);
    
    VkSurfaceKHR surface;
    if (vkCreateWin32SurfaceKHR(instance, &surface_create_info, NULL, &surface) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create Vulkan surface.\n");
        vkDestroyInstance(instance, NULL);
        DestroyWindow(global_hwnd);
        free(vulkan_state);
        return NULL;
    }
    vulkan_state->surface = surface;
    
    // Pick physical device
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, NULL);
    if (device_count == 0) {
        fprintf(stderr, "No Vulkan-compatible devices found.\n");
        vkDestroySurfaceKHR(instance, surface, NULL);
        vkDestroyInstance(instance, NULL);
        DestroyWindow(global_hwnd);
        free(vulkan_state);
        return NULL;
    }
    
    VkPhysicalDevice* physical_devices = malloc(device_count * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(instance, &device_count, physical_devices);
    
    // For simplicity, just pick the first device
    VkPhysicalDevice physical_device = physical_devices[0];
    vulkan_state->physical_device = physical_device;
    free(physical_devices);
    
    // Create logical device
    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_create_info = {0};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = 0; // Assume first queue family
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    
    VkDeviceCreateInfo device_create_info = {0};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount = 1;
    device_create_info.pQueueCreateInfos = &queue_create_info;
    device_create_info.enabledExtensionCount = 1;
    const char* device_extensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    device_create_info.ppEnabledExtensionNames = device_extensions;
    
    VkDevice device;
    if (vkCreateDevice(physical_device, &device_create_info, NULL, &device) != VK_SUCCESS) {
        fprintf(stderr, "Failed to create logical device.\n");
        vkDestroySurfaceKHR(instance, surface, NULL);
        vkDestroyInstance(instance, NULL);
        DestroyWindow(global_hwnd);
        free(vulkan_state);
        return NULL;
    }
    vulkan_state->device = device;
    
    printf("Vulkan initialized successfully.\n");
    return vulkan_state;
}

// Function to shutdown Vulkan
void shutdown_vulkan(VulkanState* vulkan_state) {
    if (vulkan_state != NULL) {
        printf("Shutting down Vulkan...\n");
        
        if (vulkan_state->device) {
            vkDestroyDevice(vulkan_state->device, NULL);
        }
        if (vulkan_state->surface) {
            vkDestroySurfaceKHR(vulkan_state->instance, vulkan_state->surface, NULL);
        }
        if (vulkan_state->instance) {
            vkDestroyInstance(vulkan_state->instance, NULL);
        }
        if (global_hwnd) {
            DestroyWindow(global_hwnd);
        }
        
        free(vulkan_state);
        printf("Vulkan shutdown complete.\n");
    }
}

// Function to handle Vulkan input events
void handle_vulkan_input_events(VulkanState* vulkan_state) {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
        // Check for quit message
        if (msg.message == WM_QUIT) {
            vulkan_state->running = false;
        }
        // Check for ESC key
        else if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE) {
            vulkan_state->running = false;
        }
    }
}

// Function to render with Vulkan
void render_vulkan(VulkanState* vulkan_state) {
    // Simple clear screen with different color
    static float color[3] = {0.0f, 0.0f, 0.0f};
    static float color_step = 0.01f;
    
    // Update color for visual feedback
    color[0] += color_step;
    if (color[0] > 1.0f || color[0] < 0.0f) {
        color_step = -color_step;
        color[0] = fmax(0.0f, fmin(1.0f, color[0]));
    }
    
    // In a real implementation, this would do actual Vulkan rendering
    // For now, we'll just sleep to simulate work
    Sleep(16);
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Function to create Vulkan window surface
bool create_vulkan_surface(VulkanState* vulkan_state, void* window) {
    // This is already handled in initialize_vulkan
    (void)vulkan_state;
    (void)window;
    return true;
}