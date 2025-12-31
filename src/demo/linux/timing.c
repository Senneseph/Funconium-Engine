#include "timing.h"
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Platform-independent sleep function
void sleep_ms(uint32_t milliseconds) {
    #ifdef _WIN32
    Sleep(milliseconds);
    #else
    usleep(milliseconds * 1000);
    #endif
}

// Simple display refresh rate detection (placeholder implementation)
// In a real implementation, this would use platform-specific APIs
bool detect_display_refresh_rate(DisplayInfo* display_info) {
    if (display_info == NULL) {
        return false;
    }

    // Default values - in a real implementation, these would be detected
    display_info->width = 1920;
    display_info->height = 1080;
    display_info->refresh_rate_hz = 60; // Default to 60Hz
    display_info->device_name = "Primary Display";

    // TODO: Implement actual display detection using platform-specific APIs
    // For Linux: X11/XRandR or Wayland APIs
    // For Windows: EnumDisplaySettings or DXGI
    // For macOS: Core Graphics APIs

    return true;
}

// Calculate optimal frame delay based on actual refresh rate
uint32_t calculate_frame_delay_ms(uint32_t refresh_rate_hz) {
    if (refresh_rate_hz == 0) {
        return TARGET_FRAME_TIME_MS; // Fallback to default
    }
    
    // Calculate frame time based on refresh rate
    // We target slightly less than the full frame time to account for processing overhead
    uint32_t frame_time_ms = 1000 / refresh_rate_hz;
    
    // Use 90% of frame time to leave room for processing
    return (uint32_t)(frame_time_ms * 0.9);
}

// Function to get current time in nanoseconds
uint64_t get_current_time_ns() {
    #ifdef _WIN32
    // Windows implementation using QueryPerformanceCounter
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (uint64_t)((counter.QuadPart * 1000000000) / frequency.QuadPart);
    #else
    // POSIX implementation using clock_gettime
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec;
    #endif
}