# Vector Database Pipeline Specifications

## Overview

The vector database pipeline is the core of the Funconium Engine's rendering system. It handles the assembly of the 3D scene by treating each pixel as a 4-point z-axis "slice" of the scene. This slice forms a long rectangular solid, with four points in each corner tracing out until they hit a vector database object.

## Architecture

The vector database pipeline is designed to leverage vector database techniques for rendering scenes, avoiding traditional BSP trees and other conventional methods. The architecture focuses on utilizing AVX512 FP16 instructions on CPUs and similar optimizations on GPUs to create a unified rendering pipeline. The pipeline takes a highly functional approach, where input parameters come in, and output parameters come out. Object-oriented inheritance patterns are not as important as interface and API shapes.

### Functional Approach

The pipeline is designed to operate on a unified memory pool, where functions operate on subsections of this pool and produce new/replacement parts as they work their way down the function chain. This approach emphasizes more evaluations of expressions than jumping, branching, or looping, allowing for highly asynchronous execution within a single thread and making job systems feasible.

### Language Considerations

The pipeline is designed to be implemented in a language that supports a highly functional approach, with long-tail friendly functions. The focus is on creating a library (C++ or C) with modular components that can be optimized independently. The language should support efficient memory management and allow for highly asynchronous execution within a single thread.

### Rendering as a Time-Domain Problem

The vector database pipeline treats rendering as a time-domain problem, where each pixel owns a view-space volume defined by the eye position and the pixel's footprint on the screen, forming a 4-sided pyramid (frustum). The renderer spends time inside that volume until the frame deadline hits, then collapses the accumulated result into a single pixel color. This approach is closer to path tracing, beam tracing, or cone tracing but driven by time, not sample count.

### Pixel-Centric Rendering

The pipeline adopts a pixel-centric rendering approach, where each pixel maintains accumulated radiance, variance/confidence, motion sensitivity, and perceptual importance. The scheduler decides per frame which pixels get more refinement, which pixels can coast on stale data, and which pixels need emergency attention. This turns rendering into a real-time scheduling problem, not a graphics one.

### Eye Tracking and Perceptual Importance

The pipeline leverages eye tracking to prioritize pixels near the gaze center, providing deeper sampling and smaller error tolerance. Pixels during saccades can reuse old data or skip refinement. This approach avoids classic foveated rendering with rings and instead uses continuous priority falloff per pixel per frame, eliminating hard boundaries and artifacts.

## Key Components

### 1. Pixel Slice Generation

For each pixel, generate a 4-point z-axis slice. This slice is a rectangular solid that extends into the scene.

#### Pixel Slice Details:

- **Slice Generation**: Each pixel generates a 4-point z-axis slice. This slice is a rectangular solid that extends into the scene.
- **Slice Properties**: The slice is defined by four points in each corner, tracing out until they hit a vector database object.

### 2. Vector Database Query

Trace the points through the vector database to determine intersections with objects. The vector database is optimized for fast queries using AVX512 FP16 instructions on the CPU and similar optimizations on the GPU.

#### Vector Database Details:

- **Database Structure**: The vector database stores objects in a way that allows for fast queries. Each object is represented as a set of vectors that define its boundaries and properties.
- **Query Optimization**: The vector database is optimized for fast queries using AVX512 FP16 instructions on the CPU and similar optimizations on the GPU.

### 3. Object Rendering

Render objects as they are intersected by the slices. This allows for efficient rendering of complex scenes.

#### Object Rendering Details:

- **Intersection Detection**: The slices are traced through the vector database to detect intersections with objects. This is done using optimized algorithms that leverage AVX512 FP16 instructions on the CPU and similar optimizations on the GPU.
- **Rendering**: Objects are rendered as they are intersected by the slices. This allows for efficient rendering of complex scenes without the need for traditional BSP trees or other conventional methods.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the pipeline as a modular component that can be optimized independently.

## Implementation Details

### Pixel Slice Generation

The pixel slice generation process involves generating a 4-point z-axis slice for each pixel. This slice is a rectangular solid that extends into the scene, defined by four points in each corner.

### Vector Database Query

The vector database query process involves tracing the slices through the vector database to detect intersections with objects. The vector database is optimized for fast queries using AVX512 FP16 instructions on the CPU and similar optimizations on the GPU.

### Object Rendering

The object rendering process involves rendering objects as they are intersected by the slices. This allows for efficient rendering of complex scenes without the need for traditional BSP trees or other conventional methods.

## Conclusion

The vector database pipeline specifications outline the core of the Funconium Engine's rendering system, focusing on leveraging vector database techniques to create a unified rendering pipeline that efficiently utilizes both CPU and GPU resources. The architecture is designed to meet a desired FPS by dynamically scaling the workload and allows for out-of-order rendering and the application of effects.