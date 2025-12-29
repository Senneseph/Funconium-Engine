# Core Engine Specifications

## Overview

The core engine is the foundation of the Funconium Engine, responsible for managing the overall architecture, including the vector database pipeline, CPU/GPU scheduler, early rendering mechanism, and compositing and effects.

## Architecture

The core engine is designed to leverage vector database techniques for rendering scenes, avoiding traditional BSP trees and other conventional methods. The architecture focuses on utilizing AVX512 FP16 instructions on CPUs and similar optimizations on GPUs to create a unified rendering pipeline. The engine takes a highly functional approach, where input parameters come in, and output parameters come out. Object-oriented inheritance patterns are not as important as interface and API shapes.

### Functional Approach

The engine is designed to operate on a unified memory pool, where functions operate on subsections of this pool and produce new/replacement parts as they work their way down the function chain. This approach emphasizes more evaluations of expressions than jumping, branching, or looping, allowing for highly asynchronous execution within a single thread and making job systems feasible.

### Language Considerations

The engine is designed to be implemented in a language that supports a highly functional approach, with long-tail friendly functions. The focus is on creating a library (C++ or C) with modular components that can be optimized independently. The language should support efficient memory management and allow for highly asynchronous execution within a single thread.

### Rendering as a Time-Domain Problem

The core engine treats rendering as a time-domain problem, where each pixel owns a view-space volume defined by the eye position and the pixel's footprint on the screen, forming a 4-sided pyramid (frustum). The renderer spends time inside that volume until the frame deadline hits, then collapses the accumulated result into a single pixel color. This approach is closer to path tracing, beam tracing, or cone tracing but driven by time, not sample count.

### Pixel-Centric Rendering

The engine adopts a pixel-centric rendering approach, where each pixel maintains accumulated radiance, variance/confidence, motion sensitivity, and perceptual importance. The scheduler decides per frame which pixels get more refinement, which pixels can coast on stale data, and which pixels need emergency attention. This turns rendering into a real-time scheduling problem, not a graphics one.

### Eye Tracking and Perceptual Importance

The engine leverages eye tracking to prioritize pixels near the gaze center, providing deeper sampling and smaller error tolerance. Pixels during saccades can reuse old data or skip refinement. This approach avoids classic foveated rendering with rings and instead uses continuous priority falloff per pixel per frame, eliminating hard boundaries and artifacts.

## Key Components

### 1. Vector Database Pipeline

The vector database pipeline is the core of the Funconium Engine's rendering system. It handles the assembly of the 3D scene by treating each pixel as a 4-point z-axis "slice" of the scene. This slice forms a long rectangular solid, with four points in each corner tracing out until they hit a vector database object.

#### Pipeline Steps:

1. **Pixel Slice Generation**: For each pixel, generate a 4-point z-axis slice.
2. **Vector Database Query**: Trace the points through the vector database to determine intersections with objects.
3. **Object Rendering**: Render objects as they are intersected by the slices.

### 2. CPU/GPU Scheduler

The CPU/GPU scheduler is designed to meet a desired FPS by dynamically scaling the workload based on available compute power. The game slice rendering continues processing until the timer for the frame expires.

#### Scheduler Features:

- **Deadline-Based**: Ensures that the rendering process adheres to the desired FPS.
- **Dynamic Scaling**: Jobs are scaled to utilize all available compute power.
- **Max Settings**: The engine always operates at maximum settings for the given FPS, eliminating the need for manual adjustments.

### 3. Early Rendering Mechanism

The early rendering mechanism allows the GPU to start rendering as soon as the entity's state for the next frame is determined, without waiting for the entire game loop to complete.

#### Early Rendering Steps:

1. **Entity Update**: The CPU updates the entity's state for the next frame.
2. **Immediate Rendering**: The updated entity is passed to the GPU for rendering into a temporary buffer.
3. **Compositing**: The temporary buffers are blended to form the final frame.

### 4. Compositing and Effects

The compositing and effects mechanism blends the temporary buffers to create the final scene, allowing for out-of-order rendering and the application of effects.

#### Compositing Steps:

1. **Layer Blending**: Layers from the temporary buffers are blended to form the final scene.
2. **Effect Application**: Effects such as lighting, shadows, and post-processing are applied.
3. **Final Output**: The final frame is generated and displayed.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the engine as a library (C++ or C) with modular components that can be optimized independently.

## Implementation Details

### Vector Database

The vector database is optimized for fast queries using AVX512 FP16 instructions on the CPU and similar optimizations on the GPU. This allows for efficient tracing of the 4-point z-axis slices through the scene.

### CPU/GPU Scheduler

The scheduler is designed to dynamically scale the workload based on the available compute power. This ensures that the engine always operates at maximum settings for the given FPS.

### Early Rendering

Entities are updated in the CPU game loop, and as soon as their state for the next frame is determined, they are passed to the GPU for immediate rendering into a temporary buffer. This allows for out-of-order rendering and the application of effects.

### Compositing

Compositing involves blending the temporary buffers to create the final scene. This allows for the application of effects such as lighting, shadows, and post-processing.

## Conclusion

The core engine specifications outline the foundation of the Funconium Engine, focusing on leveraging vector database techniques to create a unified rendering pipeline that efficiently utilizes both CPU and GPU resources. The architecture is designed to meet a desired FPS by dynamically scaling the workload and allows for out-of-order rendering and the application of effects.