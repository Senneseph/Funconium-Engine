#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <stddef.h>

// Define the Asset structure
typedef struct {
    void* data;
    size_t size;
    char* name;
} Asset;

// Function to load an asset from a file
Asset load_asset(const char* file_path);

// Function to free an asset
void free_asset(Asset asset);

#endif // ASSET_LOADER_H