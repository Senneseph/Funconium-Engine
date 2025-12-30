#ifndef TIMING_H
#define TIMING_H

#include <stdbool.h>
#include <stdint.h>

// Frame timing constants
#define TARGET_FPS 60
#define TARGET_FRAME_TIME_MS (1000 / TARGET_FPS)
#define TARGET_FRAME_TIME_US (TARGET_FRAME_TIME_MS * 1000)

// Display refresh rate detection
typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t refresh_rate_hz;
    const char* device_name;
} DisplayInfo;

// Function to detect display refresh rate
bool detect_display_refresh_rate(DisplayInfo* display_info);

// Platform-independent sleep function
void sleep_ms(uint32_t milliseconds);

// Function to calculate optimal frame delay based on actual refresh rate
uint32_t calculate_frame_delay_ms(uint32_t refresh_rate_hz);

#endif // TIMING_H