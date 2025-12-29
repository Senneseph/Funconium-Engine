CC = gcc
CFLAGS = -I. -Wall -Wextra -std=c99 -DUSE_SDL -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2

SRC_FILES = src/demo/asset_loader.c src/demo/demo.c src/demo/main.c
OBJ_FILES = src/demo/asset_loader.o src/demo/demo.o src/demo/main.o

TARGET = dragon_raiders_demo

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(LDFLAGS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run