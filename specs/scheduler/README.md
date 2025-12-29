# CPU/GPU Scheduler Specifications

This directory contains the specifications for the CPU/GPU scheduler, which is responsible for managing the workload to meet the desired FPS.

## Overview

The CPU/GPU scheduler is designed to meet a desired FPS by dynamically scaling the workload based on available compute power. The game slice rendering continues processing until the timer for the frame expires.

## Key Components

- **Deadline-Based Scheduling**: Ensures that the rendering process adheres to the desired FPS.
- **Dynamic Scaling**: Jobs are scaled to utilize all available compute power.
- **Max Settings**: The engine always operates at maximum settings for the given FPS, eliminating the need for manual adjustments.

## Scheduler Features

1. **Frame Start**: The frame starts with the CPU updating entities.
2. **Update Entities**: Entities are updated based on the game logic.
3. **Schedule Jobs**: Jobs are scheduled dynamically based on the available compute power.
4. **Render Slices**: The vector database pipeline renders the slices.
5. **Compositing**: The temporary buffers are composited to form the final frame.
6. **Frame End**: The frame is displayed, and the process repeats.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the scheduler as a modular component that can be optimized independently.

## Getting Started

To explore the CPU/GPU scheduler specifications, refer to the following subdirectories:

- **deadline/**: Deadline-based scheduling specifications
- **scaling/**: Dynamic scaling specifications
- **jobs/**: Job scheduling specifications