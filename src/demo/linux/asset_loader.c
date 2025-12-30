#include "asset_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to duplicate a string
char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* dup = malloc(len);
    if (dup != NULL) {
        memcpy(dup, str, len);
    }
    return dup;
}

// Function to load an asset from a file
Asset load_asset(const char* file_path) {
    Asset asset = {NULL, 0, NULL};

    // Open the file
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", file_path);
        return asset;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the asset data
    void* data = malloc(file_size);
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate memory for asset data.\n");
        fclose(file);
        return asset;
    }

    // Read the file data
    size_t bytes_read = fread(data, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Failed to read file data.\n");
        free(data);
        fclose(file);
        return asset;
    }

    // Close the file
    fclose(file);

    // Allocate memory for the asset name
    char* name = strdup(file_path);
    if (name == NULL) {
        fprintf(stderr, "Failed to allocate memory for asset name.\n");
        free(data);
        return asset;
    }

    // Set the asset properties
    asset.data = data;
    asset.size = file_size;
    asset.name = name;

    return asset;
}

// Function to free an asset
void free_asset(Asset asset) {
    if (asset.data != NULL) {
        free(asset.data);
    }
    if (asset.name != NULL) {
        free(asset.name);
    }
}