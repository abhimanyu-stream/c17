# Variables
CC = gcc
CCFLAGS = -Wall -Wextra -std=c17 -mconsole  # for console application
TARGET = program
SRC = BinaryTree.c Main.c
HEADERS = BinaryTree.h

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CCFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
.PHONY: clean
clean:
	rm -f $(TARGET)