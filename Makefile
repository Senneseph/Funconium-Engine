# Makefile for Funconium Engine Demo
# Supports both WASM and Linux builds

# Emscripten settings for WASM build
EMCC = emcc
EM_CFLAGS = -I. -Wall -Wextra -std=gnu99 -s USE_SDL=2 -s SDL2_IMAGE_FORMATS='["png"]' -s SDL2_MIXER_FORMATS='["wav"]'
EM_LDFLAGS = -s USE_SDL=2 -s SDL2_IMAGE_FORMATS='["png"]' -s SDL2_MIXER_FORMATS='["wav"]'

# GCC settings for Linux build
GCC = gcc
GCC_CFLAGS = -I. -I./src/demo/core -Wall -Wextra -std=c99 -DUSE_SDL -I/usr/include/SDL2 -D_REENTRANT
GCC_LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# Source files for WASM build
WASM_SRC_FILES = src/demo/wasm/asset_loader.c src/demo/wasm/demo.c src/demo/wasm/main.c
WASM_OBJ_FILES = src/demo/wasm/asset_loader.o src/demo/wasm/demo.o src/demo/wasm/main.o

# Source files for Linux build
LINUX_SRC_FILES = src/demo/linux/asset_loader.c src/demo/linux/demo.c src/demo/linux/main.c src/demo/core/demo_core.c src/demo/linux/sdl_wrapper.c src/demo/linux/logger.c src/demo/linux/timing.c src/demo/linux/layout_engine.c
LINUX_OBJ_FILES = src/demo/linux/asset_loader.o src/demo/linux/demo.o src/demo/linux/main.o src/demo/core/demo_core.o src/demo/linux/sdl_wrapper.o src/demo/linux/logger.o src/demo/linux/timing.o src/demo/linux/layout_engine.o

# Targets
WASM_TARGET = demo.html
LINUX_TARGET = dragon_raiders_demo

# Default target
all: $(LINUX_TARGET)

# Linux build
$(LINUX_TARGET): $(LINUX_OBJ_FILES)
	$(GCC) $(GCC_CFLAGS) -o $@ $(LINUX_OBJ_FILES) $(GCC_LDFLAGS) -lm

# WASM build
wasm: $(WASM_OBJ_FILES)
	$(EMCC) $(EM_CFLAGS) -o $(WASM_TARGET) $(WASM_OBJ_FILES) $(EM_LDFLAGS) -lm

# Object file rules for Linux
src/demo/linux/%.o: src/demo/linux/%.c
	$(GCC) $(GCC_CFLAGS) -c $< -o $@

# Object file rules for core
src/demo/core/%.o: src/demo/core/%.c
	$(GCC) $(GCC_CFLAGS) -c $< -o $@

# Object file rules for WASM
src/demo/wasm/%.o: src/demo/wasm/%.c
	$(EMCC) $(EM_CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(LINUX_OBJ_FILES) $(WASM_OBJ_FILES) $(LINUX_TARGET) $(WASM_TARGET)

# Run target for Linux
run:
	./$(LINUX_TARGET)

.PHONY: all clean run wasm
