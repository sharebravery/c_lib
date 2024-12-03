# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

# Source files and output directory
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)  # Source files in the src directory
BIN_DIR = bin
TARGETS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRC))

# Default target: Build all executables
all: $(BIN_DIR) $(TARGETS)

# Create the output directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile each source file into a corresponding executable in the bin directory
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# Clean up build artifacts
clean:
	rm -rf $(BIN_DIR)

# Rebuild everything from scratch
rebuild: clean all

# Phony targets to prevent conflicts with file names
.PHONY: all clean rebuild
