#!/bin/bash

# Check if the platform argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 [linux|wasm]"
    exit 1
fi

PLATFORM=$1

# Source the Emscripten environment if compiling for WASM
if [ "$PLATFORM" = "wasm" ]; then
    source /home/jsmille/emsdk/emsdk_env.sh
fi

# Navigate to the project directory
cd /home/jsmille/Projects/Funconium\ Engine

# Compile the demo based on the platform
if [ "$PLATFORM" = "linux" ]; then
    make all
elif [ "$PLATFORM" = "wasm" ]; then
    make wasm
else
    echo "Invalid platform. Use 'linux' or 'wasm'."
    exit 1
fi

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    if [ "$PLATFORM" = "linux" ]; then
        echo "Compilation successful. Running the Linux demo..."
        ./dragon_raiders_demo
    elif [ "$PLATFORM" = "wasm" ]; then
        echo "Compilation successful. Opening the demo in a browser..."
        xdg-open demo.html
    fi
else
    echo "Compilation failed. Please check the errors above."
fi
