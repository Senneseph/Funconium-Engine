#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <stddef.h>

// Define the Asset structure
typedef struct {
    void* data;
    size_t size;
    char* path;
} Asset;

// Function to load an asset
Asset load_asset(const char* path);

// Function to free an asset
void free_asset(Asset asset);

#endif // ASSET_LOADER_H