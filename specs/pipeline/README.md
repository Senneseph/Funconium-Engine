# Vector Database Pipeline Specifications

This directory contains the specifications for the vector database pipeline, which is the core of the Funconium Engine's rendering system.

## Overview

The vector database pipeline is responsible for handling the assembly of the 3D scene by treating each pixel as a 4-point z-axis "slice" of the scene. This slice forms a long rectangular solid, with four points in each corner tracing out until they hit a vector database object.

## Key Components

- **Pixel Slice Generation**: For each pixel, generate a 4-point z-axis slice.
- **Vector Database Query**: Trace the points through the vector database to determine intersections with objects.
- **Object Rendering**: Render objects as they are intersected by the slices.

## Pipeline Steps

1. **Pixel Slice Generation**: Each pixel generates a 4-point z-axis slice. This slice is a rectangular solid that extends into the scene.
2. **Vector Database Query**: The slices are traced through the vector database to find intersections with objects. The vector database is optimized for fast queries using AVX512 FP16 instructions on the CPU and similar optimizations on the GPU.
3. **Object Rendering**: Objects are rendered as they are intersected by the slices. This allows for efficient rendering of complex scenes.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the pipeline as a modular component that can be optimized independently.

## Getting Started

To explore the vector database pipeline specifications, refer to the following subdirectories:

- **generation/**: Pixel slice generation specifications
- **query/**: Vector database query specifications
- **rendering/**: Object rendering specifications