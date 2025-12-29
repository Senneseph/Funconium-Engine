# CPU/GPU Scheduler Specifications

## Overview

The CPU/GPU scheduler is responsible for managing the workload to meet the desired FPS. It is designed to meet a desired FPS by dynamically scaling the workload based on available compute power. The game slice rendering continues processing until the timer for the frame expires.

## Architecture

The CPU/GPU scheduler is designed to dynamically scale the workload based on the available compute power. This ensures that the engine always operates at maximum settings for the given FPS. The scheduler takes a highly functional approach, where input parameters come in, and output parameters come out. Object-oriented inheritance patterns are not as important as interface and API shapes.

### Functional Approach

The scheduler is designed to operate on a unified memory pool, where functions operate on subsections of this pool and produce new/replacement parts as they work their way down the function chain. This approach emphasizes more evaluations of expressions than jumping, branching, or looping, allowing for highly asynchronous execution within a single thread and making job systems feasible.

### Language Considerations

The scheduler is designed to be implemented in a language that supports a highly functional approach, with long-tail friendly functions. The focus is on creating a library (C++ or C) with modular components that can be optimized independently. The language should support efficient memory management and allow for highly asynchronous execution within a single thread.

### Rendering as a Time-Domain Problem

The CPU/GPU scheduler treats rendering as a time-domain problem, where each pixel owns a view-space volume defined by the eye position and the pixel's footprint on the screen, forming a 4-sided pyramid (frustum). The renderer spends time inside that volume until the frame deadline hits, then collapses the accumulated result into a single pixel color. This approach is closer to path tracing, beam tracing, or cone tracing but driven by time, not sample count.

### Pixel-Centric Rendering

The scheduler adopts a pixel-centric rendering approach, where each pixel maintains accumulated radiance, variance/confidence, motion sensitivity, and perceptual importance. The scheduler decides per frame which pixels get more refinement, which pixels can coast on stale data, and which pixels need emergency attention. This turns rendering into a real-time scheduling problem, not a graphics one.

### Eye Tracking and Perceptual Importance

The scheduler leverages eye tracking to prioritize pixels near the gaze center, providing deeper sampling and smaller error tolerance. Pixels during saccades can reuse old data or skip refinement. This approach avoids classic foveated rendering with rings and instead uses continuous priority falloff per pixel per frame, eliminating hard boundaries and artifacts.

## Key Components

### 1. Deadline-Based Scheduling

Ensures that the rendering process adheres to the desired FPS. The scheduler operates on a deadline-based system where the goal is to meet a desired FPS. The frame rendering process continues until the deadline is reached.

#### Deadline-Based Details:

- **Deadline Calculation**: The deadline is calculated based on the desired FPS. The scheduler ensures that the rendering process adheres to this deadline.
- **Frame Rendering**: The frame rendering process continues until the deadline is reached. This ensures that the desired FPS is met.

### 2. Dynamic Scaling

Jobs are scaled dynamically based on the available compute power. This ensures that the engine always operates at maximum settings for the given FPS.

#### Dynamic Scaling Details:

- **Workload Distribution**: Jobs are distributed dynamically based on the available compute power. This ensures that the workload is distributed evenly across the CPU and GPU.
- **Scaling Algorithm**: The scaling algorithm ensures that the engine always operates at maximum settings for the given FPS.

### 3. Max Settings

The engine always operates at maximum settings for the given FPS, eliminating the need for manual adjustments.

#### Max Settings Details:

- **Automatic Adjustment**: The engine automatically adjusts the settings to ensure that it always operates at maximum settings for the given FPS.
- **Performance Optimization**: The engine is optimized to achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the scheduler as a modular component that can be optimized independently.

## Implementation Details

### Deadline-Based Scheduling

The deadline-based scheduling process involves calculating the deadline based on the desired FPS and ensuring that the rendering process adheres to this deadline. The frame rendering process continues until the deadline is reached.

### Dynamic Scaling

The dynamic scaling process involves distributing jobs dynamically based on the available compute power. This ensures that the workload is distributed evenly across the CPU and GPU.

### Max Settings

The max settings process involves automatically adjusting the settings to ensure that the engine always operates at maximum settings for the given FPS. The engine is optimized to achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.

## Conclusion

The CPU/GPU scheduler specifications outline the core of the Funconium Engine's scheduling system, focusing on leveraging dynamic scaling and deadline-based scheduling to create a unified rendering pipeline that efficiently utilizes both CPU and GPU resources. The architecture is designed to meet a desired FPS by dynamically scaling the workload and allows for out-of-order rendering and the application of effects.