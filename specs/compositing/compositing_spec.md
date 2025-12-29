# Compositing and Effects Specifications

## Overview

The compositing and effects mechanism is responsible for blending the temporary buffers to create the final scene, allowing for out-of-order rendering and the application of effects.

## Architecture

The compositing and effects mechanism is designed to blend the temporary buffers to form the final scene, allowing for out-of-order rendering and the application of effects. The mechanism takes a highly functional approach, where input parameters come in, and output parameters come out. Object-oriented inheritance patterns are not as important as interface and API shapes.

### Functional Approach

The mechanism is designed to operate on a unified memory pool, where functions operate on subsections of this pool and produce new/replacement parts as they work their way down the function chain. This approach emphasizes more evaluations of expressions than jumping, branching, or looping, allowing for highly asynchronous execution within a single thread and making job systems feasible.

### Language Considerations

The mechanism is designed to be implemented in a language that supports a highly functional approach, with long-tail friendly functions. The focus is on creating a library (C++ or C) with modular components that can be optimized independently. The language should support efficient memory management and allow for highly asynchronous execution within a single thread.

### Rendering as a Time-Domain Problem

The compositing and effects mechanism treats rendering as a time-domain problem, where each pixel owns a view-space volume defined by the eye position and the pixel's footprint on the screen, forming a 4-sided pyramid (frustum). The renderer spends time inside that volume until the frame deadline hits, then collapses the accumulated result into a single pixel color. This approach is closer to path tracing, beam tracing, or cone tracing but driven by time, not sample count.

### Pixel-Centric Rendering

The mechanism adopts a pixel-centric rendering approach, where each pixel maintains accumulated radiance, variance/confidence, motion sensitivity, and perceptual importance. The scheduler decides per frame which pixels get more refinement, which pixels can coast on stale data, and which pixels need emergency attention. This turns rendering into a real-time scheduling problem, not a graphics one.

### Eye Tracking and Perceptual Importance

The mechanism leverages eye tracking to prioritize pixels near the gaze center, providing deeper sampling and smaller error tolerance. Pixels during saccades can reuse old data or skip refinement. This approach avoids classic foveated rendering with rings and instead uses continuous priority falloff per pixel per frame, eliminating hard boundaries and artifacts.

## Key Components

### 1. Layer Blending

Layers from the temporary buffers are blended to form the final scene. This allows for out-of-order rendering and the application of effects.

#### Layer Blending Details:

- **Layer Management**: Layers from the temporary buffers are blended to form the final scene. This allows for out-of-order rendering and the application of effects. The blending process is optimized to leverage the vector database for efficient layer management.
- **Blending Process**: The blending process is optimized to leverage the vector database for efficient layer management. This allows for efficient rendering of complex scenes.

### 2. Effect Application

Effects such as lighting, shadows, and post-processing are applied. This includes applying masks and blending layers to create the final scene.

#### Effect Application Details:

- **Effect Management**: Effects such as lighting, shadows, and post-processing are applied. This includes applying masks and blending layers to create the final scene. The effects are applied in a way that leverages the vector database for efficient processing.
- **Effect Processing**: The effects are applied in a way that leverages the vector database for efficient processing. This allows for efficient rendering of complex scenes.

### 3. Final Output

The final frame is generated and displayed. This involves combining the blended layers and applying the final effects to create the output frame.

#### Final Output Details:

- **Output Generation**: The final frame is generated and displayed. This involves combining the blended layers and applying the final effects to create the output frame.
- **Output Processing**: The output processing involves combining the blended layers and applying the final effects to create the output frame. This allows for efficient rendering of complex scenes.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the compositing and effects mechanism as a modular component that can be optimized independently.

## Implementation Details

### Layer Blending

The layer blending process involves blending layers from the temporary buffers to form the final scene. This allows for out-of-order rendering and the application of effects. The blending process is optimized to leverage the vector database for efficient layer management.

### Effect Application

The effect application process involves applying effects such as lighting, shadows, and post-processing. This includes applying masks and blending layers to create the final scene. The effects are applied in a way that leverages the vector database for efficient processing.

### Final Output

The final output process involves generating the final frame and displaying it. This involves combining the blended layers and applying the final effects to create the output frame.

## Conclusion

The compositing and effects specifications outline the core of the Funconium Engine's compositing system, focusing on leveraging layer blending and effect application to create a unified rendering pipeline that efficiently utilizes both CPU and GPU resources. The architecture is designed to meet a desired FPS by dynamically scaling the workload and allows for out-of-order rendering and the application of effects.