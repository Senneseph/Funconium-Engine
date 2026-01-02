#include "timing.h"
#include <windows.h>
#include <stdint.h>

// Function to get current time in nanoseconds
uint64_t get_current_time_ns() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
    
    if (!QueryPerformanceFrequency(&frequency)) {
        return 0;
    }
    
    if (!QueryPerformanceCounter(&counter)) {
        return 0;
    }
    
    // Convert to nanoseconds
    return (counter.QuadPart * 1000000000) / frequency.QuadPart;
}

// Function to sleep for a specified number of milliseconds
void sleep_ms(uint32_t milliseconds) {
    Sleep(milliseconds);
}