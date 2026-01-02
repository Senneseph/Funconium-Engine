#include "asset_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to load an asset
Asset load_asset(const char* path) {
    Asset asset = {NULL, 0, NULL};
    
    // Open the file
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open asset file: %s\n", path);
        return asset;
    }
    
    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fprintf(stderr, "Invalid file size for asset: %s\n", path);
        fclose(file);
        return asset;
    }
    
    // Allocate memory for the asset data
    void* data = malloc(file_size);
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate memory for asset: %s\n", path);
        fclose(file);
        return asset;
    }
    
    // Read the file data
    size_t bytes_read = fread(data, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Failed to read complete asset data: %s\n", path);
        free(data);
        fclose(file);
        return asset;
    }
    
    // Allocate memory for the path
    char* path_copy = strdup(path);
    if (path_copy == NULL) {
        fprintf(stderr, "Failed to allocate memory for asset path: %s\n", path);
        free(data);
        fclose(file);
        return asset;
    }
    
    // Close the file
    fclose(file);
    
    // Populate the asset structure
    asset.data = data;
    asset.size = file_size;
    asset.path = path_copy;
    
    return asset;
}

// Function to free an asset
void free_asset(Asset asset) {
    if (asset.data != NULL) {
        free(asset.data);
    }
    if (asset.path != NULL) {
        free(asset.path);
    }
}