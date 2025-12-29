CC = gcc
CFLAGS = -I. -Wall -Wextra -std=c99
LDFLAGS = 

SRC_DIRS = src/core src/scheduler src/rendering src/compositing src/demo
SRC_FILES = $(wildcard $(SRC_DIRS)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

TARGET = funconium_demo

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run