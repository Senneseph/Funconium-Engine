# Funconium Engine MVP Plan

## Overview

The goal of this MVP is to create a functional demo of the Funconium Engine that includes:
- Registering controls
- Drawing a screen
- Playing sound
- Graceful startup and shutdown
- A menu with options and the ability to quit
- Binding ALT+F4 to quit

The Funconium Engine is designed to leverage **time-domain rendering**, where each pixel owns a view-space volume (frustum) and the renderer spends time inside that volume until the frame deadline hits. This approach treats rendering as a real-time scheduling problem, not a graphics one.

## Architecture

The Funconium Engine will be designed using a functional approach with C structs and functions. The architecture will include:

### 1. Core Engine Components

#### Pixel Frustum Generation
- **Pixel Frustum Generation**: Generate a 4-sided pyramid (frustum) for each pixel.
- **View-Space Volume Calculation**: Calculate the view-space volume for each pixel.
- **Per-Pixel Rendering**: Render each pixel based on the view-space volume and time budget.

#### CPU/GPU Scheduler
- **Deadline-Based Scheduling**: Ensure rendering adheres to the desired FPS.
- **Dynamic Scaling**: Scale workload based on available compute power.
- **Max Settings**: Operate at maximum settings for the given FPS.

#### Early Rendering Mechanism
- **Entity Update**: Update entity states for the next frame.
- **Immediate Rendering**: Pass updated entities to the GPU for rendering into a temporary buffer.
- **Compositing**: Blend temporary buffers to form the final frame.

#### Compositing and Effects
- **Layer Blending**: Blend layers from temporary buffers to form the final scene.
- **Effect Application**: Apply effects such as lighting, shadows, and post-processing.

### 2. Demo Components

#### Controls
- **Input Handling**: Register and handle user inputs (keyboard, mouse, etc.).
- **Menu Navigation**: Allow users to navigate through menu options.
- **Quit Functionality**: Bind ALT+F4 to quit the demo.

#### Screen Drawing
- **Rendering**: Draw the screen using the early rendering mechanism.
- **Scene Assembly**: Assemble the game scene using the pixel frustum generation.

#### Sound
- **Audio Playback**: Play sound effects and background music.
- **Audio Management**: Manage audio resources and playback.

#### Startup and Shutdown
- **Initialization**: Initialize the engine and demo components gracefully.
- **Cleanup**: Clean up resources and shut down the engine gracefully.

## Implementation Steps

### Step 1: Design the Architecture
- Create a detailed architecture diagram for the Funconium Engine.
- Define the interfaces and APIs for each component.
- Outline the data structures and functions required for each component.

### Step 2: Implement the Core Engine Components
- **Pixel Frustum Generation**: Implement pixel frustum generation, view-space volume calculation, and per-pixel rendering.
- **CPU/GPU Scheduler**: Implement deadline-based scheduling, dynamic scaling, and max settings.
- **Early Rendering Mechanism**: Implement entity update, immediate rendering, and compositing.
- **Compositing and Effects**: Implement layer blending and effect application.

### Step 3: Develop the Demo
- **Controls**: Implement input handling, menu navigation, and quit functionality.
- **Screen Drawing**: Implement rendering and scene assembly.
- **Sound**: Implement audio playback and management.
- **Startup and Shutdown**: Implement initialization and cleanup.

### Step 4: Integrate the Provided Assets
- Extract and integrate the provided assets (`dark-knight-spiked-black-armored-warrior.zip` and `pieta-cinematic-wings.zip`) into the demo.
- Ensure the assets are loaded and displayed correctly.

### Step 5: Test and Validate the MVP
- Test the core engine components to ensure they function as expected.
- Test the demo to ensure controls, screen drawing, sound, and startup/shutdown work correctly.
- Validate the integration of the provided assets.
- Ensure the demo meets the MVP requirements.

## Detailed Component Specifications

### Pixel Frustum Generation

#### Pixel Frustum Generation
- **Function**: `generate_pixel_frustum`
- **Input**: Pixel coordinates, eye position, screen dimensions
- **Output**: 4-sided pyramid (frustum) for the pixel

#### View-Space Volume Calculation
- **Function**: `calculate_view_space_volume`
- **Input**: Pixel frustum, scene data
- **Output**: View-space volume for the pixel

#### Per-Pixel Rendering
- **Function**: `render_pixel`
- **Input**: View-space volume, time budget
- **Output**: Rendered pixel color

### CPU/GPU Scheduler

#### Deadline-Based Scheduling
- **Function**: `schedule_frame`
- **Input**: Desired FPS, current time
- **Output**: Frame deadline

#### Dynamic Scaling
- **Function**: `scale_workload`
- **Input**: Available compute power, workload
- **Output**: Scaled workload

#### Max Settings
- **Function**: `set_max_settings`
- **Input**: Desired FPS
- **Output**: Maximum settings for the given FPS

### Early Rendering Mechanism

#### Entity Update
- **Function**: `update_entity`
- **Input**: Entity state, next frame state
- **Output**: Updated entity state

#### Immediate Rendering
- **Function**: `render_entity`
- **Input**: Updated entity state
- **Output**: Rendered entity in temporary buffer

#### Compositing
- **Function**: `composite_frame`
- **Input**: Temporary buffers
- **Output**: Final frame

### Compositing and Effects

#### Layer Blending
- **Function**: `blend_layers`
- **Input**: Temporary buffers, blending parameters
- **Output**: Blended layers

#### Effect Application
- **Function**: `apply_effects`
- **Input**: Blended layers, effects
- **Output**: Final scene with effects

### Demo Components

#### Controls
- **Function**: `register_controls`
- **Input**: Control mappings
- **Output**: Registered controls

#### Screen Drawing
- **Function**: `draw_screen`
- **Input**: Scene data
- **Output**: Rendered screen

#### Sound
- **Function**: `play_sound`
- **Input**: Sound file, playback parameters
- **Output**: Audio playback

#### Startup and Shutdown
- **Function**: `initialize_engine`
- **Input**: Engine configuration
- **Output**: Initialized engine

- **Function**: `shutdown_engine`
- **Input**: Engine state
- **Output**: Cleaned up engine

## Conclusion

This plan outlines the steps required to create the MVP for the Funconium Engine and its demo, aligned with the time-domain rendering approach. By following this plan, we will ensure that the engine and demo meet the specified requirements and provide a solid foundation for future development.