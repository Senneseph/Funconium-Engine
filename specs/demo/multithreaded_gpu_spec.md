# Multi-threaded and GPU Memory Budgeting Features

## Overview

The multi-threaded and GPU memory budgeting features are designed to showcase the capabilities of the Funconium Engine in handling multi-threaded execution and GPU memory management. The goal is to create a system where each CPU core has at least one dedicated thread that is governable via IPC, and GPU memory is automatically budgeted for each CPU thread to ensure dedicated access to GPU resources.

## Architecture

The multi-threaded and GPU memory budgeting features are designed to operate within the Funconium Engine's unified memory pool, where functions operate on subsections of this pool and produce new/replacement parts as they work their way down the function chain. This approach emphasizes more evaluations of expressions than jumping, branching, or looping, allowing for highly asynchronous execution within a single thread and making job systems feasible.

## Key Components

### 1. Multi-threaded Execution

The multi-threaded execution system is responsible for managing the execution of tasks across multiple CPU cores. This includes:

- **Thread Management**: Manages the creation, execution, and termination of threads across multiple CPU cores.
- **Task Scheduling**: Schedules tasks to be executed on available threads, ensuring that each CPU core has at least one dedicated thread.
- **IPC Governance**: Governs the execution of threads via IPC, allowing for communication and coordination between threads.

#### Multi-threaded Execution Details:

- **Thread Management**: The thread management system is responsible for creating, executing, and terminating threads across multiple CPU cores. This includes managing the lifecycle of threads and ensuring that each CPU core has at least one dedicated thread.
- **Task Scheduling**: The task scheduling system is responsible for scheduling tasks to be executed on available threads. This includes prioritizing tasks based on their importance and ensuring that tasks are distributed evenly across available threads.
- **IPC Governance**: The IPC governance system is responsible for governing the execution of threads via IPC. This includes managing communication and coordination between threads, ensuring that threads can work together to achieve common goals.

### 2. GPU Memory Budgeting

The GPU memory budgeting system is responsible for managing the allocation and usage of GPU memory. This includes:

- **Memory Allocation**: Allocates GPU memory to each CPU thread, ensuring that each thread has dedicated access to GPU resources.
- **Memory Management**: Manages the usage of GPU memory, ensuring that memory is used efficiently and effectively.
- **Memory Budgeting**: Budgets GPU memory for each CPU thread, ensuring that each thread has access to the resources it needs to execute tasks effectively.

#### GPU Memory Budgeting Details:

- **Memory Allocation**: The memory allocation system is responsible for allocating GPU memory to each CPU thread. This includes ensuring that each thread has dedicated access to GPU resources and that memory is allocated in a way that maximizes performance.
- **Memory Management**: The memory management system is responsible for managing the usage of GPU memory. This includes ensuring that memory is used efficiently and effectively, and that memory is freed when it is no longer needed.
- **Memory Budgeting**: The memory budgeting system is responsible for budgeting GPU memory for each CPU thread. This includes ensuring that each thread has access to the resources it needs to execute tasks effectively, and that memory is allocated in a way that maximizes performance.

## Performance Goals

- **Maximize AVX512 Utilization**: Achieve near 99% of theoretical performance by pre-computing necessary instructions and data, dynamically unrolling loops, and minimizing overhead.
- **Buffering**: Implement buffering techniques to minimize dead clock cycles, aiming for 1 dead clock cycle for every 1024 bits processed.
- **Modularity**: Design the multi-threaded and GPU memory budgeting features as a modular component that can be optimized independently.

## Implementation Details

### Multi-threaded Execution

The multi-threaded execution process involves managing the execution of tasks across multiple CPU cores. This includes creating, executing, and terminating threads across multiple CPU cores, scheduling tasks to be executed on available threads, and governing the execution of threads via IPC.

### GPU Memory Budgeting

The GPU memory budgeting process involves managing the allocation and usage of GPU memory. This includes allocating GPU memory to each CPU thread, managing the usage of GPU memory, and budgeting GPU memory for each CPU thread.

## Conclusion

The multi-threaded and GPU memory budgeting features specifications outline the core of the Funconium Engine's multi-threaded and GPU memory budgeting system, focusing on leveraging multi-threaded execution and GPU memory management to create a system that efficiently utilizes both CPU and GPU resources. The architecture is designed to meet a desired FPS by dynamically scaling the workload and allows for out-of-order rendering and the application of effects.