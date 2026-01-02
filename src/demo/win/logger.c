#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Global logger state
static FILE* log_file = NULL;
static size_t current_log_size = 0;
static size_t max_log_size = 0;
static CRITICAL_SECTION log_critical_section;

// Function to initialize the logger
bool initialize_logger(LoggerConfig* config) {
    if (config == NULL) {
        return false;
    }

    // Initialize critical section for thread safety
    InitializeCriticalSection(&log_critical_section);

    // Open the log file in append mode
    log_file = fopen(config->log_file_path, "a");
    if (log_file == NULL) {
        return false;
    }

    max_log_size = config->max_log_size;

    // Get current log size
    fseek(log_file, 0, SEEK_END);
    current_log_size = ftell(log_file);
    fseek(log_file, 0, SEEK_END);

    return true;
}

// Function to log a message
void log_message(const char* message) {
    if (log_file == NULL || message == NULL) {
        return;
    }

    EnterCriticalSection(&log_critical_section);

    // Get current time
    SYSTEMTIME st;
    GetSystemTime(&st);

    // Write timestamp and message
    fprintf(log_file, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, message);

    // Flush to ensure message is written
    fflush(log_file);

    // Update current log size
    current_log_size += strlen(message) + 30; // Approximate size

    // Check if log size exceeds maximum
    if (current_log_size > max_log_size && max_log_size > 0) {
        // Rotate log file
        fclose(log_file);
        
        char rotated_path[256];
        snprintf(rotated_path, sizeof(rotated_path), "%s.old", "demo.log");
        
        // Delete old rotated file if it exists
        DeleteFileA(rotated_path);
        
        // Rename current log to rotated
        MoveFileA("demo.log", rotated_path);
        
        // Reopen log file
        log_file = fopen("demo.log", "a");
        if (log_file == NULL) {
            LeaveCriticalSection(&log_critical_section);
            return;
        }
        
        current_log_size = 0;
    }

    LeaveCriticalSection(&log_critical_section);
}

// Function to shutdown the logger
void shutdown_logger() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }

    DeleteCriticalSection(&log_critical_section);
}