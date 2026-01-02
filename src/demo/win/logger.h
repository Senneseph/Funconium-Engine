#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>

// Logger configuration structure
typedef struct {
    const char* log_file_path;
    size_t max_log_size;
} LoggerConfig;

// Function to initialize the logger
bool initialize_logger(LoggerConfig* config);

// Function to log a message
void log_message(const char* message);

// Function to shutdown the logger
void shutdown_logger();

#endif // LOGGER_H