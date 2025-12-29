# Early Rendering Mechanism Specifications

## Overview

The early rendering mechanism is designed to allow the GPU to start rendering as soon as the entity's state for the next frame is determined, without waiting for the entire game loop to complete.

## Architecture

The early rendering mechanism is designed to allow the GPU to start rendering as soon as the entity's state for the next frame is determined, without waiting for the entire game loop to complete. The mechanism takes a highly functional approach, where input parameters come in, and output parameters come out. Object-oriented inheritance patterns are not as important as interface and API shapes.

### Functional Approach

The mechanism is designed to operate on a unified memory pool, where functions operate on subsections of this pool and produce new/replacement parts as they work their way down the function chain. This approach emphasizes more evaluations of expressions than jumping, branching, or looping, allowing for highly asynchronous execution within a single thread and making job systems feasible.

### Language Considerations

The mechanism is designed to be implemented in a language that supports a highly functional approach, with long-tail friendly functions. The focus is on creating a library (C++ or C) with modular components that can be optimized independently. The language should support efficient memory management and allow for highly asynchronous execution within a single thread.

### Rendering as a Time-Domain Problem

The early rendering mechanism treats rendering as a time-domain problem, where each pixel owns a view-space volume defined by the eye position and the pixel's footprint on the screen, forming a 4-sided pyramid (frustum). The renderer spends time inside that volume until the frame deadline hits, then collapses the accumulated result into a single pixel color. This approach is closer to path tracing, beam tracing, or cone tracing but driven by time, not sample count.

### Pixel-Centric Rendering

The mechanism adopts a pixel-centric rendering approach, where each pixel maintains accumulated radiance, variance/confidence, motion sensitivity, and perceptual importance. The scheduler decides per frame which pixels get more refinement, which pixels can coast on stale data, and which pixels need emergency attention. This turns rendering into a real-time scheduling problem, not a graphics one.

### Eye Tracking and Perceptual Importance

The mechanism leverages eye tracking to prioritize pixels near the gaze center, providing deeper sampling and smaller error tolerance. Pixels during saccades can reuse old data or skip refinement. This approach avoids classic foveated rendering with rings and instead uses continuous priority falloff per pixel per frame, eliminating hard boundaries and artifacts.

## Key Components

### 1. Entity Update

The CPU updates the entity's state for the next frame. This includes updating the entity's position, orientation, and other properties.

#### Entity Update Details:

- **State Update**: The CPU updates the entity's state for the next frame. This includes updating the entity's position, orientation, and other properties such as lighting and textures.
- **Immediate Rendering**: The updated entity is passed to the GPU for rendering into a temporary buffer. This allows the GPU to start rendering as soon as the entity's state is updated, without waiting for the entire game loop to complete.

### 2. Immediate Rendering

The updated entity is passed to the GPU for rendering into a temporary buffer. This allows the GPU to start rendering as soon as the entity's state is updated, without waiting for the entire game loop to complete.

#### Immediate Rendering Details:

- **GPU Rendering**: The updated entity is passed to the GPU for rendering into a temporary buffer. This allows the GPU to start rendering as soon as the entity's state is updated, without waiting for the entire game loop to complete.
- **Temporary Buffer**: The temporary buffer is used to store the rendered entity. This allows for efficient rendering of complex scenes.

### 3. Compositing

The temporary buffers are blended to form the final frame. This involves combining the rendered entities and applying effects.

#### Compositing Details:

- **Layer Blending**: Layers from the temporary buffers are blended to form the final scene. This allows for out-of-order rendering and the application of effects.
- **Effect Application**: Effects such as lighting, shadows, and post-processing are applied. This includes applying masks and blending layers to create the final scene.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the early rendering mechanism as a modular component that can be optimized independently.

## Implementation Details

### Entity Update

The entity update process involves updating the entity's state for the next frame. This includes updating the entity's position, orientation, and other properties such as lighting and textures.

### Immediate Rendering

The immediate rendering process involves passing the updated entity to the GPU for rendering into a temporary buffer. This allows the GPU to start rendering as soon as the entity's state is updated, without waiting for the entire game loop to complete.

### Compositing

The compositing process involves blending the temporary buffers to form the final frame. This involves combining the rendered entities and applying effects such as lighting, shadows, and post-processing.

## Conclusion

The early rendering mechanism specifications outline the core of the Funconium Engine's rendering system, focusing on leveraging early rendering to create a unified rendering pipeline that efficiently utilizes both CPU and GPU resources. The architecture is designed to meet a desired FPS by dynamically scaling the workload and allows for out-of-order rendering and the application of effects.
