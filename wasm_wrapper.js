// JavaScript wrapper for the WASM module
// This file handles rendering to the canvas and input events

// Global variables for the canvas and context
let canvas = null;
let ctx = null;
let wasmModule = null;

// Initialize the canvas and context
function initCanvas() {
    canvas = document.getElementById('canvas');
    if (!canvas) {
        console.error('Canvas element not found');
        return false;
    }
    ctx = canvas.getContext('2d');
    if (!ctx) {
        console.error('Failed to get canvas context');
        return false;
    }
    return true;
}

// Clear the canvas
function clearCanvas() {
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
}

// Draw a rectangle on the canvas
function drawRect(x, y, width, height, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x, y, width, height);
}

// Handle keyboard input
function handleKeyDown(event) {
    if (event.key === 'Escape') {
        // Call the quit function in the WASM module
        if (wasmModule && wasmModule._quit_demo) {
            wasmModule._quit_demo();
        }
    }
}

// Main function to initialize the WASM module and set up event listeners
function main() {
    // Initialize the canvas
    if (!initCanvas()) {
        return;
    }

    // Set up event listeners
    document.addEventListener('keydown', handleKeyDown);

    console.log('WASM module initialized and ready');
}

// Start the application
main();
