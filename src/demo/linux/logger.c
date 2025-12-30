#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

// Global logger configuration
static LoggerConfig logger_config = {0};
static FILE* log_file = NULL;

// Function to initialize the logger
bool initialize_logger(LoggerConfig* config) {
    if (config == NULL) {
        fprintf(stderr, "Logger config is NULL.\n");
        return false;
    }

    logger_config = *config;

    // Open the log file in append mode
    log_file = fopen(logger_config.log_file_path, "a");
    if (log_file == NULL) {
        fprintf(stderr, "Failed to open log file: %s\n", logger_config.log_file_path);
        return false;
    }

    // Check the log file size and prune if necessary
    struct stat st;
    if (stat(logger_config.log_file_path, &st) == 0) {
        if (st.st_size > logger_config.max_log_size) {
            // Prune the log file by removing the first half
            FILE* temp_file = fopen("temp_log.txt", "w");
            if (temp_file == NULL) {
                fprintf(stderr, "Failed to create temporary log file.\n");
                fclose(log_file);
                log_file = NULL;
                return false;
            }

            // Seek to the middle of the log file
            fseek(log_file, st.st_size / 2, SEEK_SET);

            // Copy the remaining content to the temporary file
            char buffer[1024];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), log_file)) > 0) {
                fwrite(buffer, 1, bytes_read, temp_file);
            }

            fclose(log_file);
            fclose(temp_file);

            // Replace the original log file with the temporary file
            remove(logger_config.log_file_path);
            rename("temp_log.txt", logger_config.log_file_path);

            // Reopen the log file
            log_file = fopen(logger_config.log_file_path, "a");
            if (log_file == NULL) {
                fprintf(stderr, "Failed to reopen log file: %s\n", logger_config.log_file_path);
                return false;
            }
        }
    }

    return true;
}

// Function to log a message
void log_message(const char* format, ...) {
    if (log_file == NULL) {
        return;
    }

    // Get the current time
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // Write the timestamp to the log file
    fprintf(log_file, "[%s] ", timestamp);

    // Write the log message to the log file
    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    // Add a newline
    fprintf(log_file, "\n");

    // Flush the log file to ensure the message is written immediately
    fflush(log_file);

    // Check the log file size and prune if necessary
    struct stat st;
    if (stat(logger_config.log_file_path, &st) == 0) {
        if (st.st_size > logger_config.max_log_size) {
            // Prune the log file by removing the first half
            FILE* temp_file = fopen("temp_log.txt", "w");
            if (temp_file == NULL) {
                fprintf(stderr, "Failed to create temporary log file.\n");
                return;
            }

            // Seek to the middle of the log file
            fseek(log_file, st.st_size / 2, SEEK_SET);

            // Copy the remaining content to the temporary file
            char buffer[1024];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), log_file)) > 0) {
                fwrite(buffer, 1, bytes_read, temp_file);
            }

            fclose(log_file);
            fclose(temp_file);

            // Replace the original log file with the temporary file
            remove(logger_config.log_file_path);
            rename("temp_log.txt", logger_config.log_file_path);

            // Reopen the log file
            log_file = fopen(logger_config.log_file_path, "a");
            if (log_file == NULL) {
                fprintf(stderr, "Failed to reopen log file: %s\n", logger_config.log_file_path);
                return;
            }
        }
    }
}

// Function to shutdown the logger
void shutdown_logger() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}