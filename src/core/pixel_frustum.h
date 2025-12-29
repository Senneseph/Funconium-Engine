#ifndef PIXEL_FRUSTUM_H
#define PIXEL_FRUSTUM_H

#include <stddef.h>

// Define the PixelFrustum structure
typedef struct {
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    float x4, y4, z4;
} PixelFrustum;

// Define the ViewSpaceVolume structure
typedef struct {
    PixelFrustum frustum;
    float accumulated_radiance;
    float variance;
    float motion_sensitivity;
    float perceptual_importance;
} ViewSpaceVolume;

// Function to generate a pixel frustum
PixelFrustum generate_pixel_frustum(float x, float y, float eye_x, float eye_y, float eye_z, float screen_width, float screen_height);

// Function to calculate the view-space volume for a pixel
ViewSpaceVolume calculate_view_space_volume(PixelFrustum frustum, void* scene_data);

// Function to render a pixel based on the view-space volume and time budget
void render_pixel(ViewSpaceVolume volume, float time_budget);

#endif // PIXEL_FRUSTUM_H
