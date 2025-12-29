# Core Engine Specifications

This directory contains the core specifications for the Funconium Engine. The core engine is responsible for managing the overall architecture, including the vector database pipeline, CPU/GPU scheduler, early rendering mechanism, and compositing and effects.

## Overview

The core engine is designed to leverage vector database techniques for rendering scenes, avoiding traditional BSP trees and other conventional methods. The architecture focuses on utilizing AVX512 FP16 instructions on CPUs and similar optimizations on GPUs to create a unified rendering pipeline.

## Key Components

- **Vector Database Pipeline**: Each pixel spawns its own 4-point z-axis "slice" of the scene, effectively a long rectangular solid. Four points in each corner trace out until they hit a vector database object.
- **CPU/GPU Scheduler**: A deadline-based scheduler ensures that the desired FPS is met by dynamically scaling the workload based on available compute power.
- **Early Rendering Mechanism**: Entities are updated in the CPU game loop, and as soon as their state for the next frame is determined, they are passed to the GPU for immediate rendering into a temporary buffer.
- **Compositing and Effects**: Layers from the temporary buffers are blended to form the final scene, allowing for out-of-order rendering and the application of effects.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the engine as a library (C++ or C) with modular components that can be optimized independently.

## Getting Started

To explore the core engine specifications, refer to the following subdirectories:

- **pipeline/**: Vector database pipeline specifications
- **scheduler/**: CPU/GPU scheduler specifications
- **rendering/**: Early rendering mechanism specifications
- **compositing/**: Compositing and effects specifications
- **performance/**: Performance optimization specifications