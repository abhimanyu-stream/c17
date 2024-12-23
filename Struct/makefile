# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c17

# Target executable name
TARGET = basic-knowledge-struct.exe

# Source files
SRC = basic-knowledge-struct.c

# Build rules
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove the compiled executable
clean:
	del /f $(TARGET)


# End of makefile
