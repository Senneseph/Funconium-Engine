#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>

// Function to get current time in nanoseconds
uint64_t get_current_time_ns();

// Function to sleep for a specified number of milliseconds
void sleep_ms(uint32_t milliseconds);

#endif // TIMING_H